#include <QColorDialog>
#include <QErrorMessage>
#include <QMessageBox>
#include <QInputDialog>
#include "PhyloGUI/inc/mainwindow.h"
#include "PhyloGUI/ui_mainwindow.h"
#include "PhyloGUI/inc/graphwidget.h"
#include "Domain/ITree.h"
#include "PhyloGUI/inc/filedialog.h"

using namespace DataSource;



MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    graph = new GraphWidget(ui->frame);
    graph->setAttribute(Qt::WA_DeleteOnClose, true);
    ui->actionClear_selection->setEnabled(false);
    ui->actionColor_nodes->setEnabled(false);
    ui->actionSelect_all_nodes->setEnabled(false);
    ui->actionSelect_descendants->setEnabled(false);
    ui->actionSelect_Ancestors->setEnabled(false);
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
    FileDialog fileDialog(this);

    if (fileDialog.exec())
    {
        ui->listWidget->clear();

        FilesInfo filesInfo(fileDialog.getTreesFile(), fileDialog.getLocationsFile(), fileDialog.getDistancesFile());

        loadTree(filesInfo);
    }
    //else not needed: user closed or canceled the dialog
}

void MainWindow::loadTree(const FilesInfo& info)
{
    FileDataSource<GuiNode>fileDataSource;

    try
    {
        fileDataSource.load(info, trees);

        ListIterator< ITree<GuiNode> > iter = trees.getIterator();

        for(; !iter.end(); iter.next())
        {
            QListWidgetItem* newItem = new QListWidgetItem;
            newItem->setText(QString(info.getTreesFilePath().c_str()));
            ui->listWidget->addItem(newItem);
        }
    }
    catch (const DataFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load data file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
        trees.clear();
    }
    catch (const TreeFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load tree file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
        trees.clear();
    }
    catch (const DistancesFileException& ex)
    {
        QMessageBox msg(QMessageBox::Information, "Load distances file error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
        trees.clear();
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

void MainWindow::on_actionOptions_triggered()
{

}

void MainWindow::on_actionColor_nodes_triggered()
{
    QColor color = QColorDialog::getColor();
    if (color.isValid())
    {
        graph->paintNode(color, actualTree);
    }
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
        cout << "Search for: " << text.toStdString();
    }
    //else not needed
}

void MainWindow::drawTree()
{
    ui->actionClear_selection->setEnabled(true);
    ui->actionColor_nodes->setEnabled(true);
    ui->actionSelect_all_nodes->setEnabled(true);
    ui->actionSelect_descendants->setEnabled(true);
    ui->actionSelect_Ancestors->setEnabled(true);
    actualTree = trees.elementAt(ui->listWidget->currentRow());
    graph->draw(actualTree);
}

