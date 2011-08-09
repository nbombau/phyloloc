#include <QColorDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QInputDialog>

#include "PhyloGUI/inc/mainwindow.h"
#include "PhyloGUI/ui_mainwindow.h"
#include "PhyloGUI/inc/graphwidget.h"
#include "Domain/ITree.h"
#include "PhyloGUI/inc/filedialog.h"
#include "PhyloGUI/inc/propagatedialog.h"
#include "Phyloloc/Propagator/Propagator.h"
#include "Phylopp/Searching/SearchNode.h"


using namespace DataSource;
using namespace Propagation;
using namespace Searching;
using namespace PhyloGUI;


MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //nodesSelectedCount = 0;
    actualTree = NULL;
    graph = new GraphWidget(ui->splitter);
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
    ui->splitter->addWidget(graph);
    QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(drawTree()), Qt::QueuedConnection);

    Propagator<GuiNode>::correctRoundMode();
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
    FileDialog fileDialog(this);

    if (fileDialog.exec())
    {
        ui->listWidget->clear();

        FilesInfo filesInfo(fileDialog.getTreesFile(), fileDialog.getLocationsFile(), fileDialog.getDistancesFile());

        loadTree(filesInfo, fileDialog.isMissingDataCheckBoxChecked());
    }
    //else not needed: user closed or canceled the dialog
}

void MainWindow::loadTree(const FilesInfo& info, bool allowMissingData)
{
    FileDataSource<GuiNode>fileDataSource;

    try
    {
        fileDataSource.load(info, trees, allowMissingData);

        ITreeCollection<GuiNode>::iterator iter = trees.getIterator();

        for (; !iter.end(); iter.next())
        {
            QListWidgetItem* newItem = new QListWidgetItem;
            QString path(info.getTreesFilePath().c_str());
            newItem->setToolTip(path);
            newItem->setText(path);
            ui->listWidget->addItem(newItem);
        }
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
        sn.search(searchString);
    }
    //else not needed
}

void MainWindow::on_actionProcess_tree_triggered()
{
    PropagateDialog propagate(this);
    if (propagate.exec())
    {
        try
        {
            Propagator<GuiNode>::propagate(actualTree, propagate.getPasses(), propagate.getGCF(), propagate.getBCLF());
            QListIterator<QGraphicsItem*> items(graph->scene()->items());
            while (items.hasNext())
            {
                items.next()->update();
            }
            QMessageBox msg(QMessageBox::Information, "Propagation finished"
                            , "The propagation has ended.\n\nPlausibility vector is now available in the node's detail."
                            , QMessageBox::NoButton, this);
            msg.exec();
        }
        catch (const PropagationException& ex)
        {
            QMessageBox msg(QMessageBox::Information, "Propagation error", ex.what(), QMessageBox::NoButton, this);
            msg.exec();
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
    ui->actionProcess_tree->setEnabled(true);
    ui->actionSearch_terminal_nodes->setEnabled(true);
    ui->actionZoom->setEnabled(true);
    ui->actionZoom_2->setEnabled(true);
    actualTree = trees.elementAt(ui->listWidget->currentRow());
    graph->draw(actualTree);
}


void MainWindow::on_actionZoom_triggered()
{
    graph->scaleView(1.2);
}

void MainWindow::on_actionZoom_2_triggered()
{
    graph->scaleView(0.8);
}
/*
void MainWindow::nodeSelected(int nodeAction)
{
    if(nodeAction==0)
        ++nodesSelectedCount;
    else
        --nodesSelectedCount;

    if(nodesSelectedCount>0)
        activateMenuItems(true);
    else
        activateMenuItems(false);
}

void MainWindow::activateMenuItems(bool activate)
{
    ui->actionColor_nodes->setEnabled(activate);
    ui->actionSelect_descendants->setEnabled(activate);
    ui->actionSelect_Ancestors->setEnabled(activate);
}*/
