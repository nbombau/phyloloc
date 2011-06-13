#include <QColorDialog>
#include <QErrorMessage>
#include <QMessageBox>

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
    ui->actionClear_selection->setEnabled(false);
    ui->actionColor_nodes->setEnabled(false);
    ui->actionSelect_all_nodes->setEnabled(false);
    ui->actionSelect_descendants->setEnabled(false);
    ui->actionSelect_Ancestors->setEnabled(false);
    QObject::connect(ui->listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(drawTree()), Qt::QueuedConnection);
}

MainWindow::~MainWindow()
{
    //delete graph;
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
    }
    catch (const std::exception& ex)
    {
        QMessageBox msg(QMessageBox::Information, "load error", ex.what(), QMessageBox::NoButton, this);
        msg.exec();
    }

    ListIterator< ITree<GuiNode> > *iter = trees.getIterator();

    unsigned int i = 0;

    while (!iter->end())
    {
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setText(QString(info.getTreesFilePath().c_str()));
        ui->listWidget->addItem(newItem);

        iter->next();
        ++i;
    }
    delete iter;
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
