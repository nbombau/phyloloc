#include <QFileDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <limits>
#include "PhyloGUI/inc/nodedetaildialog.h"

using namespace PhyloGUI;
using namespace std;

NodeDetailDialog::NodeDetailDialog(Domain::NodeName& name,
                                   Locations::Location& locations,
                                   Propagation::LocationProbabilities& probabilities,
                                   Locations::LocationManager& locationManager,
                                   QWidget* parent)
    : QDialog(parent),
      propGrid(NULL),
      consGrid(NULL)

{
    this->setBaseSize(400, 100);
    setFixedSize(baseSize());

    this->setWindowTitle("Propagation");
    const int leftMargin = 20;
    const int topMargin  = 20;
    const int labelWidth = 500;

    const int loadButtonWidth = 100;
    const int height = 25;
    int top = topMargin;

    nameLabel = new QLabel(this);
    nameLabel->setText("Name: ");
    nameLabel->setGeometry(leftMargin, top, labelWidth, height);

    nameText = new QLabel(this);
    nameText->setWordWrap(true);
    nameText->setText(QString(name.empty()?"No information available":name.c_str()));
    nameText->setGeometry(leftMargin+80, top, labelWidth, height);
    top += height;

    locationLabel = new QLabel(this);
    locationLabel->setText("Location: ");
    locationLabel->setGeometry(leftMargin, top, labelWidth, height);

    locationText = new QLabel(this);
    locationText->setWordWrap(true);
    locationText->setText(QString(locations.empty()?"No information available":locations.c_str()));
    locationText->setGeometry(leftMargin+80, top, labelWidth, height);
    top += height;

    /*
    * If the node has no probabilities this means the propagation hasn't
    * happen. The dialog whil not contain grid and will be smaller.
    */
    if(probabilities.size()!=0)
    {
        this->setBaseSize(450, 550);
        setFixedSize(baseSize());

        //Set probabilities table
        propGrid = new QTableWidget(probabilities.size(),2,this);
        propGrid->setBaseSize(425,100);
        propGrid->setGeometry(leftMargin, top, 410, 200);
        propGrid->setColumnWidth(0,260);
        propGrid->setColumnWidth(1,100);
        QStringList propTitles("Location");
        propTitles.append(QString("Probabilities"));
        propGrid->setHorizontalHeaderLabels(propTitles);
        VariantsSet::iterator it = locationManager.getLocations();
        for(unsigned int i=0; i<probabilities.size(); ++i,it++)
        {
            QTableWidgetItem * prob=new QTableWidgetItem(QString().setNum(probabilities[i], 'f', 3));
            prob->setFlags(Qt::NoItemFlags);
            propGrid->setItem(i,1,prob);

            QTableWidgetItem * location=new QTableWidgetItem(QString(it->second.c_str()));
            location->setFlags(Qt::NoItemFlags);
            propGrid->setItem(i,0,location);
        }

        top += height+200;

        //Set consensus table
        consGrid = new QTableWidget(1500,6,this);
        consGrid->setBaseSize(425,100);
        consGrid->setGeometry(leftMargin, top, 410, 200);
        consGrid->setColumnWidth(0,260);
        consGrid->setColumnWidth(1,100);
        QStringList consTitles("Location");
        consTitles.append(QString("Average"));
        consTitles.append(QString("Standard deviation"));
        consTitles.append(QString("Median"));
        consTitles.append(QString("Percentile 25"));
        consTitles.append(QString("Percentile 75"));
        consGrid->setHorizontalHeaderLabels(consTitles);
        for(unsigned int i=0; i<probabilities.size(); ++i)
        {
            QTableWidgetItem * item=new QTableWidgetItem(QString().setNum(probabilities[i], 'f', 3));
            item->setFlags(Qt::NoItemFlags);
            consGrid->setItem(i,1,item);
        }

        consGrid->resizeColumnsToContents();

        top += height+200;
    }

    propagateButton = new QPushButton(this);
    propagateButton->setGeometry((width() -loadButtonWidth) / 2, top, loadButtonWidth, height);
    propagateButton->setText("Close");

    connect(propagateButton, SIGNAL(clicked()), this, SLOT(accept()));
}

NodeDetailDialog::~NodeDetailDialog()
{
    delete nameLabel;
    delete locationLabel;
    delete nameText;
    delete locationText;
    if(propGrid!=NULL)
        delete propGrid;
    if(propGrid!=NULL)
        delete consGrid;
}
