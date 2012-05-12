#include <iostream>
#include "inc/aboutdialog.h"

using namespace PhyloGUI;

AboutDialog::AboutDialog(QWidget* parent) :
    QDialog(parent)
{
    this->setBaseSize(445, 330);
    setFixedSize(baseSize());

    this->setWindowTitle("About us");

    this->nameLabel = new QLabel(this);
    this->nameLabel->setText("<a href='http://code.google.com/p/phyloloc/' style='text-decoration:none;'><B>Phyloloc v1.0</B></a>");
    this->nameLabel->setGeometry(178, 0, 200, 30);
    this->nameLabel->setOpenExternalLinks(true);

    this->logoFudepanLabel = new QLabel(this);
    this->logoFudepanLabel->setGeometry(7, 21, 200, 150);
    this->logoFudepanLabel->setText("<a href='http://fudepan.org.ar/'><img src=':/Images/FuDePAN-logo' /></>");
    this->logoFudepanLabel->setToolTip(tr("Fundacion para el desarrollo de la Programacion en acidos Nucleicos"));
    this->logoFudepanLabel->setOpenExternalLinks(true);

    this->logoItbaLabel = new QLabel(this);
    this->logoItbaLabel->setGeometry(232, 21, 200, 150);
    this->logoItbaLabel->setText("<a href='http://www.itba.edu.ar/'><img src=':/Images/ITBA-logo' /></>");
    this->logoItbaLabel->setToolTip(tr("Instituto tecnologico de Buenos Aires"));
    this->logoItbaLabel->setOpenExternalLinks(true);

    this->logoGplLabel = new QLabel(this);
    this->logoGplLabel->setGeometry(7, 141, 200, 150);
    this->logoGplLabel->setText("<a href='http://gplv3.fsf.org//'><img src=':/Images/Gpl-logo' /></>");
    this->logoGplLabel->setToolTip(tr("GPL V3"));
    this->logoGplLabel->setOpenExternalLinks(true);

    this->logoEfpuLabel = new QLabel(this);
    this->logoEfpuLabel->setGeometry(276, 141, 200, 150);
    this->logoEfpuLabel->setText("<a href='http://www.efpu.org.ar/'><img src=':/Images/EFPU-logo' /></>");
    this->logoEfpuLabel->setToolTip(tr("Estacion de Fotobiologia Playa Union"));
    this->logoEfpuLabel->setOpenExternalLinks(true);

    this->okButton = new QPushButton(this);
    this->okButton->setText("OK");
    this->okButton->setGeometry(190, 286, 52, 28);

    connect(this->okButton, SIGNAL(clicked()), this, SLOT(okButtonAction()));
}

AboutDialog::~AboutDialog()
{
    delete this->nameLabel;
    delete this->logoEfpuLabel;
    delete this->logoFudepanLabel;
    delete this->logoGplLabel;
    delete this->logoItbaLabel;
    delete this->okButton;
}

void AboutDialog::okButtonAction()
{
    this->close();
}
