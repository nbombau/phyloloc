#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "graphwidget.h"
#include "optionsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    (new GraphWidget(ui->frame))->draw();
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

}

void MainWindow::on_actionOptions_triggered()
{
    OptionsDialog od;
    od.show();
    od.exec();
}

void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem* item)
{
    //get item select in list
    printf(item->text().toAscii().data());

    //TODO look for tree and redraw
}
