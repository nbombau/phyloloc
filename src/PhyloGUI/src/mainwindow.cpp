#include <QColorDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QInputDialog>

#include "PhyloGUI/inc/mainwindow.h"
#include "PhyloGUI/ui_mainwindow.h"
#include "PhyloGUI/inc/graphwidget.h"
#include "PhyloGUI/inc/filedialog.h"
#include "PhyloGUI/inc/aboutdialog.h"
#include "PhyloGUI/inc/propagatedialog.h"
#include "Phylopp/Searching/SearchNode.h"
#include "PhyloGUI/inc/nodedetaildialog.h"
#include "Phylopp/Consensor/StrictConsensor.h"
#include "Phyloloc/Propagator/StatisticCollectorObserver.h"
#include "Phyloloc/Propagator/DeviationPropagatorObserver.h"
#include "Phyloloc/Propagator/DeviationsExporter.h"


using namespace DataSource;
using namespace Propagation;
using namespace Searching;
using namespace PhyloGUI;
using namespace Consensus;

const int NO_CONSENSED_TREE = -1;

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    consensedTree(NULL)
{
    ui->setupUi(this);
    actualTree = NULL;
    graph = new GraphWidget(locationManager, ui->splitter);
    GuiNode::setLocationManager(&locationManager);
    graph->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->actionClear_selection->setEnabled(false);
    ui->actionColor_nodes->setEnabled(false);
    ui->actionSelect_all_nodes->setEnabled(false);
    ui->actionSelect_descendants->setEnabled(false);
    ui->actionSelect_Ancestors->setEnabled(false);
    ui->actionProcess_tree->setEnabled(false);
    ui->actionSave_As->setEnabled(false);
    ui->actionSearch_terminal_nodes->setEnabled(false);
    ui->actionZoom->setEnabled(false);
    ui->actionZoom_2->setEnabled(false);
    ui->actionActual_size->setEnabled(false);
    ui->splitter->addWidget(graph);

    QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(drawTree()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    exit(EXIT_SUCCESS);
}

void MainWindow::on_actionOpen_triggered()
{
    if (consensedTree != NULL)
    {
        QMessageBox msg(QMessageBox::Information, "Already propagated", "After propagating you need to close all the trees before loading any more. Go to File -> Close all... and load the trees again.", QMessageBox::NoButton, this);
        msg.exec();
    }
    else
    {
        FileDialog fileDialog(this);

        if (fileDialog.exec())
        {
            FilesInfo filesInfo(fileDialog.getTreesFile(), fileDialog.getLocationsFile(), fileDialog.getDistancesFile());

            loadTree(filesInfo, fileDialog.isMissingDataCheckBoxChecked(), locationManager);

            ui->actionSave_As->setEnabled(true);
        }
        //else not needed: user closed or canceled the dialog
    }
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog aboutDialog(this);

    aboutDialog.exec();


}

void MainWindow::loadTree(const FilesInfo& info, bool allowMissingData, LocationManager& locationManager)
{
    FileDataSource<GuiNode>fileDataSource;

    try
    {
        fileDataSource.load(info, trees, locationManager, allowMissingData);
    }
    catch (const DataFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load data file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
    }
    catch (const TreeFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load tree file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
    }
    catch (const DistancesFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load distances file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
    }
    catch (const InvalidLocation& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load distances file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
    }

    ui->listWidget->clear();

    ITreeCollection<GuiNode>::iterator iter = trees.getIterator();

    unsigned int treeNumber = 1;

    for (; !iter.end(); iter.next())
    {
        QListWidgetItem* newItem = new QListWidgetItem;

        std:: stringstream itemText;
        itemText << "Tree " << treeNumber;
        newItem->setText(QString(itemText.str().c_str()));

        ui->listWidget->addItem(newItem);
        treeNumber++;
    }

    if (ui->listWidget->count() != 0)
        ui->actionProcess_tree->setEnabled(true);
}

void MainWindow::on_actionSave_As_triggered()
{
    QStringList filePaths;
    QString path;
    QFileDialog dialog(this, "Save tree", QDir::homePath(), "");
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        foreach(path, filePaths)
        {
            ;
        }
    }
}

void MainWindow::on_actionColor_nodes_triggered()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
        graph->paintNode(color, actualTree);
}


void MainWindow::on_actionClear_selection_triggered()
{
    graph->unSelectAllNodes(actualTree);
}

void MainWindow::on_actionSelect_all_nodes_triggered()
{
    graph->selectAllNodes(actualTree);
}

void MainWindow::on_actionSelect_descendants_triggered()
{
    graph->selectNodeDescendants(actualTree);
}

void MainWindow::on_actionSelect_Ancestors_triggered()
{
    graph->selectNodeAncestors(actualTree);
}

void MainWindow::on_actionSearch_terminal_nodes_triggered()
{
    bool ok;
    QString text = QInputDialog::getText(this, tr("Search nodes..."),
                                         tr("Node name:"), QLineEdit::Normal,
                                         "", &ok);
    if (ok)
    {
        const std::string searchString = text.toStdString();
        SearchNode<GuiNode> sn;
        sn.setRoot(actualTree->getRoot());
        sn.search(searchString, locationManager);
    }
    //else not needed
}

void MainWindow::on_actionProcess_tree_triggered()
{
    if (consensedTree != NULL)
    {
        QMessageBox msg(QMessageBox::Information, "Already propagated", "For doing a second propagation go to File -> Close all... and load the trees again.", QMessageBox::NoButton, this);
        msg.exec();
    }
    else
    {
        PropagateDialog propagateDialog(this);
        unsigned int i = 0;
        if (propagateDialog.exec())
        {
            try
            {
                ListIterator<ITree<GuiNode> > it = trees.getIterator();
                DeviationsExporter exporter(propagateDialog.getExportPath());
                DeviationPropagatorObserver<GuiNode> obs(exporter);
                for (; !it.end(); it.next())
                {
                    if(propagateDialog.getExportDeviations())
                    {
                        Propagator<GuiNode, DeviationPropagatorObserver<GuiNode> >::propagate(it.get(),
                                                       propagateDialog.getPasses(),
                                                       propagateDialog.getGCF(),
                                                       propagateDialog.getBLCF(),
                                                       locationManager,
                                                       &obs);
                    }
                    else
                    {
                        Propagator<GuiNode>::propagate(it.get(),
                                                       propagateDialog.getPasses(),
                                                       propagateDialog.getGCF(),
                                                       propagateDialog.getBLCF(),
                                                       locationManager);
                    }                    
                    
                    ++i;
                }
                if (actualTree != NULL)
                {
                    //After propagation the items need to be redrawn (updated).
                    QListIterator<QGraphicsItem*> items(graph->scene()->items());
                    while (items.hasNext())
                    {
                        items.next()->update();
                    }
                }

                StatisticCollectorObserver<GuiNode > observer(locationManager.getLocationsCount());
                StrictConsensor<GuiNode , StatisticCollectorObserver<GuiNode > > consensor;
                consensedTree = consensor.consensus(trees, observer, locationManager);

                QListWidgetItem* newItem = new QListWidgetItem();
                newItem->setText("Consensed tree");
                ui->listWidget->addItem(newItem);
                consensedTreeRow = ui->listWidget->row(newItem);

                QMessageBox msg(QMessageBox::Information, "Propagation finished"
                                , "The propagation has ended.\n\nPlausibility vector is now available in the node's detail.\n\nA consensus tree is also available."
                                , QMessageBox::NoButton, this);
                msg.exec();
            }
            catch (const PropagationException& ex)
            {
                QMessageBox msg(QMessageBox::Information, "Propagation error", ex.what(), QMessageBox::NoButton, this);
                msg.exec();
            }
            catch (const DisjointTerminalsException& ex)
            {
                QMessageBox msg(QMessageBox::Information, "Propagation finished"
                                , "The propagation has ended.\n\nPlausibility vector is now available in the node's detail.\n\nNo consensus tree is available because the input trees have disjoint terminal nodes"
                                , QMessageBox::NoButton, this);
                msg.exec();
                consensedTreeRow = NO_CONSENSED_TREE;
            }
        }
    }
}

void MainWindow::drawTree()
{
    ui->actionClear_selection->setEnabled(true);
    ui->actionColor_nodes->setEnabled(true);
    ui->actionSelect_all_nodes->setEnabled(true);
    ui->actionSelect_descendants->setEnabled(true);
    ui->actionSelect_Ancestors->setEnabled(true);
    ui->actionSearch_terminal_nodes->setEnabled(true);
    ui->actionZoom->setEnabled(true);
    ui->actionZoom_2->setEnabled(true);
    ui->actionActual_size->setEnabled(true);
    const int row = ui->listWidget->currentRow();
    if (row == consensedTreeRow)
        graph->draw(consensedTree);
    else
    {
        actualTree = trees.elementAt(row);
        graph->draw(actualTree);
    }
}


void MainWindow::on_actionZoom_triggered()
{
    graph->scaleView(1.2);
}

void MainWindow::on_actionZoom_2_triggered()
{
    graph->scaleView(0.8);
}

void MainWindow::on_actionActual_size_triggered()
{
    graph->fitInView(graph->scene()->sceneRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_actionClose_all_triggered()
{
    QMessageBox msg(QMessageBox::Question, "Close all", "Are you sure you want to close all the trees currently open?", QMessageBox::Ok | QMessageBox::Cancel, this);
    if (msg.exec() == QMessageBox::Ok)
    {
        locationManager.clear();
        if (consensedTree != NULL)
        {
            delete consensedTree;
            consensedTree = NULL;
        }
        trees.clear();
        actualTree = NULL;
        ui->listWidget->clear();
        delete graph->scene();
        consensedTreeRow = NO_CONSENSED_TREE;
        ui->actionClear_selection->setEnabled(false);
        ui->actionColor_nodes->setEnabled(false);
        ui->actionSelect_all_nodes->setEnabled(false);
        ui->actionSelect_descendants->setEnabled(false);
        ui->actionSelect_Ancestors->setEnabled(false);
        ui->actionProcess_tree->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionSearch_terminal_nodes->setEnabled(false);
        ui->actionZoom->setEnabled(false);
        ui->actionZoom_2->setEnabled(false);
        ui->actionActual_size->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
    }
}
