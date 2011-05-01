#include <QColorDialog>
#include <QErrorMessage>

#include "PhyloGUI/inc/mainwindow.h"
#include "PhyloGUI/ui_mainwindow.h"
#include "PhyloGUI/inc/graphwidget.h"
#include "Domain/ITree.h"

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
    QStringList filePaths;
    QString path;
    QFileInfo dir;
    QFileInfo dat;

    QFileDialog dialog(this, "Open file(s)", QDir::homePath(), "");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    if (dialog.exec())
    {
        filePaths = dialog.selectedFiles();
        foreach(path, filePaths)
        {
            dir = QFileInfo(path);

            string basePath = dir.canonicalPath().toStdString() + "/" + dir.completeBaseName().toStdString();

            dat = QFileInfo(QString((basePath + ".dat").c_str()));
            if (dat.exists())
                loadTree(basePath);
            else
            {
                QErrorMessage msg(this);
                msg.showMessage(basePath.append(".dat").append(" does not exist").c_str());
                msg.exec();
            }
        }
    }
}

void MainWindow::loadTree(std::string treePath)
{

    FilesInfo info(treePath + ".nwk", treePath + ".dat");

    FileDataSource<GuiNode>fileDataSource;

    fileDataSource.load(info, trees);

    ListIterator< ITree<GuiNode> > *iter = trees.getIterator();

    unsigned int i = 0;

    while (!iter->end())
    {
        QListWidgetItem* newItem = new QListWidgetItem;
        newItem->setText(QString(treePath.c_str()));
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
    actualTree = trees.elementAt(ui->listWidget->currentRow());
    graph->draw(actualTree);
}
