#include "PhyloGUI/inc/filedialog.h"

#include <QFileDialog>
#include <QMessageBox>

FileDialog::FileDialog(QWidget *parent)
    : QDialog(parent)
{
    this->setBaseSize(450,350);
    setFixedSize(baseSize());

    this->setWindowTitle("Load files...");
    int leftMargin = 20;
    int topMargin  = 20;
    int labelWidth = 150;
    int lineWidth  = 330;
    int buttonWidth= 70;

    int loadButtonWidth= 50;
    int height = 25;
    int top = topMargin;

    distancesLabel = new QLabel(this);
    distancesLabel->setText("Load distances file:");
    distancesLabel->setGeometry(leftMargin, top, labelWidth, height);

    top +=height+5;
    distancesLine = new QLineEdit(this);
    distancesLine->setGeometry(leftMargin,top,lineWidth,height);

    distancesButton = new QPushButton(this);
    distancesButton->setGeometry(leftMargin+lineWidth+5,top,buttonWidth,height);
    distancesButton->setText("Select...");

    top+=65;

    locationsLabel = new QLabel(this);
    locationsLabel->setText("Load locations file:");
    locationsLabel->setGeometry(leftMargin, top, labelWidth, height);

    top +=height+5;
    locationsLine = new QLineEdit(this);
    locationsLine->setGeometry(leftMargin,top,lineWidth,height);

    locationsButton = new QPushButton(this);
    locationsButton->setGeometry(leftMargin+lineWidth+5,top,buttonWidth,height);
    locationsButton->setText("Select...");

    top+=65;

    treesLabel = new QLabel(this);
    treesLabel->setText("Load trees file:");
    treesLabel->setGeometry(leftMargin, top, labelWidth, height);

    top +=height+5;
    treesLine = new QLineEdit(this);
    treesLine->setGeometry(leftMargin,top,lineWidth,height);

    treesButton = new QPushButton(this);
    treesButton->setGeometry(leftMargin+lineWidth+5,top,buttonWidth,height);
    treesButton->setText("Select...");

    top +=height+25;

    loadButton = new QPushButton(this);
    loadButton->setGeometry((width()-2*loadButtonWidth-15)/2,top,loadButtonWidth,height);
    loadButton->setText("Load");

    cancelButton = new QPushButton(this);
    cancelButton->setGeometry((width()+15)/2,top,loadButtonWidth,height);
    cancelButton->setText("Cancel");

    connect(distancesButton, SIGNAL(clicked()),this, SLOT(distancesButtonAction()));
    connect(locationsButton, SIGNAL(clicked()),this, SLOT(locationsButtonAction()));
    connect(treesButton, SIGNAL(clicked()),this, SLOT(treesButtonAction()));
    connect(loadButton, SIGNAL(clicked()),this, SLOT(loadButtonAction()));
    connect(cancelButton, SIGNAL(clicked()),this, SLOT(reject()));
}

FileDialog::~FileDialog()
{
    delete distancesLabel;
    delete distancesLine;
    delete distancesButton;

    delete locationsLabel;
    delete locationsLine;
    delete locationsButton;

    delete treesLabel;
    delete treesLine;
    delete treesButton;

    delete cancelButton;
    delete loadButton;
}



void FileDialog::distancesButtonAction()
{
    QFileDialog dialog(this, "Open distances file", QDir::homePath(), "");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setFilter("Distance files (*.dist);;All files (*)");

    if (dialog.exec())
    {
        QStringList list = dialog.selectedFiles();
        QStringList::Iterator it = list.begin();
        while(it != list.end()) {
            distancesLine->setText(*it);
            ++it;
        }
    }
}

void FileDialog::locationsButtonAction()
{
    QFileDialog dialog(this, "Open locations file", QDir::homePath(), "");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setFilter("Locations files (*.dat);;All files (*)");

    if (dialog.exec())
    {
        QStringList list = dialog.selectedFiles();
        QStringList::Iterator it = list.begin();
        while(it != list.end()) {
            locationsLine->setText(*it);
            ++it;
        }
    }
}

void FileDialog::treesButtonAction()
{
    QFileDialog dialog(this, "Open trees file", QDir::homePath(), "");
    dialog.setAcceptMode(QFileDialog::AcceptOpen);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setFilter("Trees files (*.nwk);;All files (*)");

    if (dialog.exec())
    {
        QStringList list = dialog.selectedFiles();
        QStringList::Iterator it = list.begin();
        while(it != list.end()) {
            treesLine->setText(*it);
            ++it;
        }
    }
}

void FileDialog::loadButtonAction()
{
    std::string distancesFile = distancesLine->text().toStdString();
    std::string locationsFile = locationsLine->text().toStdString();
    std::string treesFile = treesLine->text().toStdString();

    if (distancesFile=="" || locationsFile=="" || treesFile=="")
    {
        QMessageBox msg(QMessageBox::Information,"Selection error","Please select a distance,location and tree files",QMessageBox::NoButton,this);
        msg.exec();
    }
    else
    {
        this->accept();
    }
}

std::string FileDialog::getLocationsFile()
{
    return locationsLine->text().toStdString();
}

std::string FileDialog::getDistancesFile()
{
    return distancesLine->text().toStdString();
}

std::string FileDialog::getTreesFile()
{
    return treesLine->text().toStdString();
}

