#include "../inc/mainwindow.h"
#include "../inc/ui_mainwindow.h"
#include "../inc/graphwidget.h"
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GraphWidget * graph=new GraphWidget(ui->frame);
    graph->draw();
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
    QFileDialog * openDialog=new QFileDialog(this,"Open file(s)",QDir::homePath(),"");
    openDialog->setAcceptMode(QFileDialog::AcceptOpen);
    openDialog->setFileMode(QFileDialog::ExistingFiles);
    if(openDialog->exec())
    {
        filePaths=openDialog->selectedFiles();
        foreach(path, filePaths)
        {
            dir=QFileInfo(path);
            QListWidgetItem *newItem = new QListWidgetItem;
            newItem->setText(dir.fileName());
            ui->listWidget->addItem(newItem);
        }
    }
}

void MainWindow::on_actionSave_As_triggered()
{
    QStringList filePaths;
    QString path;
    QFileDialog * saveDialog=new QFileDialog(this,"Save tree",QDir::homePath(),"");
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveDialog->setFileMode(QFileDialog::ExistingFiles);
    if(saveDialog->exec())
    {
        printf(saveDialog->directory().absolutePath().toAscii().data());
        filePaths=saveDialog->selectedFiles();
        foreach(path, filePaths)
        {
            printf(path.toAscii().data());
        }
    }
}

void MainWindow::on_actionOptions_triggered()
{

}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    //get item select in list
    printf(item->text().toAscii().data());
    //TODO look for tree and redraw
}

void MainWindow::on_actionExport_to_PNG_triggered()
{

}

void MainWindow::on_actionColor_nodes_triggered()
{
    QColor color=QColorDialog::getColor();
    if(color.isValid())
    {
        graph->paintNode(&color);
    }
}