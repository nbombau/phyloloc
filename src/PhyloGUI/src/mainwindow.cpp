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

    //loadTree("/home/eteisair/tmp");

    QObject::connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(drawTree()),Qt::QueuedConnection);


   // actualTree = trees.elementAt(0);

   // graph->draw(actualTree);
    /*
    GuiNode* root = actualTree.getRoot();
    root->setName("root");

    GuiNode* node = root->addChild();
    node->setBranchLength(12);
    node->setName("A");

    GuiNode* node1 = node->addChild();
    node1->setBranchLength(1);
    node1->setName("B");
    node1 = node->addChild();
    node1->setBranchLength(1);
    node1->setName("C");

    GuiNode* node2 = node1->addChild();
    node2->setBranchLength(3);
    node2->setName("B");
    node2 = node1->addChild();
    node2->setBranchLength(3);
    node2->setName("C");

    node = root->addChild();
    node->setBranchLength(5);
    node->setName("D");

    node1 = node->addChild();
    node1->setBranchLength(1);
    node1->setName("E");
    node1 = node->addChild();
    node1->setBranchLength(4);
    node1->setName("F");
    node1 = node->addChild();
    node1->setBranchLength(5);
    node1->setName("G");

    node = root->addChild();
    node->setBranchLength(3);
    node->setName("H");

    node1 = node->addChild();
    node1->setBranchLength(2);
    node1->setName("I");
    node1 = node->addChild();
    node1->setBranchLength(2);
    node1->setName("J");

    node = root->addChild();
    node->setBranchLength(8);
    node->setName("K");

    node1 = node->addChild();
    node1->setBranchLength(3);
    node1->setName("L");
    node1 = node->addChild();
    node1->setBranchLength(1);
    node1->setName("M");
    node1 = node->addChild();
    node1->setBranchLength(4);
    node1->setName("N");
    node1 = node->addChild();
    node1->setBranchLength(6);
    node1->setName("O");

    */
    //graph->draw(actualTree);

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

            string basePath= dir.canonicalPath().toStdString()+"/"+dir.completeBaseName().toStdString();

            dat=QFileInfo(QString( (basePath+".dat").c_str()));
            if(dat.exists())
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

    FilesInfo info(treePath+".nwk",treePath+".dat");

    FileDataSource<GuiNode>fileDataSource;

    fileDataSource.load(info,trees);

    ListIterator< ITree<GuiNode> > *iter = trees.getIterator();

    unsigned int i=0;

    while(!iter->end())
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
        graph->paintNode(color,actualTree);
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
    printf("Seleccionar descendientes\n");
}

void MainWindow::on_actionSelect_Ancestors_triggered()
{
    printf("Seleccionar ancestros\n");
}


void MainWindow::drawTree()
{
    std::cout << "\nCURRENT-ROW: "<< ui->listWidget->currentRow()<<"\n";

    actualTree=trees.elementAt(ui->listWidget->currentRow());

    std::cout << actualTree->getRoot()->getName();

    std::cout.flush();

    graph->draw(actualTree);
}
