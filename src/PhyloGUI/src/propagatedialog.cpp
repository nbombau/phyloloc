#include <QFileDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <limits>
#include "PhyloGUI/inc/propagatedialog.h"

using namespace PhyloGUI;
using namespace std;

PropagateDialog::PropagateDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setBaseSize(450, 350);
    setFixedSize(baseSize());

    this->setWindowTitle("Propagation");
    const int leftMargin = 20;
    const int topMargin  = 20;
    const int labelWidth = 500;
    const int lineWidth  = 80;
    //const int buttonWidth = 50;

    const int loadButtonWidth = 100;
    const int height = 25;
    int top = topMargin;

    top += height;

    BCFLLabel = new QLabel(this);
    BCFLLabel->setText("BCLF Weight (Number between 0 and 1):");
    BCFLLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;


    BCFLLine = new QDoubleSpinBox(this);
    BCFLLine->setGeometry(leftMargin, top, lineWidth, height);
    BCFLLine->setValue(0.5);
    BCFLLine->setMaximum(1.0);
    BCFLLine->setMinimum(0.0);
    BCFLLine->setSingleStep(0.1);
    BCFLLine->setDecimals(2);
    top += height + 5;

    top += height;

    GCFLabel = new QLabel(this);
    GCFLabel->setText("GCF Weight (Number between 0 and 1):");
    GCFLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;

    GCFLine = new QDoubleSpinBox(this);
    GCFLine->setGeometry(leftMargin, top, lineWidth, height);
    GCFLine->setValue(0.5);
    GCFLine->setMaximum(1.0);
    GCFLine->setMinimum(0.0);
    GCFLine->setSingleStep(0.1);
    GCFLine->setDecimals(2);
    top += height + 5;

    top += height;

    passLabel = new QLabel(this);
    passLabel->setText("Number of passes:");
    passLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;

    passLine = new QSpinBox(this);
    passLine->setGeometry(leftMargin, top, lineWidth, height);
    passLine->setValue(2);
    passLine->setMinimum(1);
    passLine->setMaximum(numeric_limits<int>::max());
    top += height + 5;

    top += height + 25;

    propagateButton = new QPushButton(this);
    propagateButton->setGeometry((width() - 2 * loadButtonWidth - 15) / 2, top, loadButtonWidth, height);
    propagateButton->setText("Propagate");

    cancelButton = new QPushButton(this);
    cancelButton->setGeometry((width() + 15) / 2, top, loadButtonWidth, height);
    cancelButton->setText("Cancel");

    connect(propagateButton, SIGNAL(clicked()), this, SLOT(acceptInput()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

PropagateDialog::~PropagateDialog()
{
    delete BCFLLabel;
    delete BCFLLine;

    delete GCFLabel;
    delete GCFLine;

    delete passLabel;
    delete passLine;

    delete cancelButton;
    delete propagateButton;
}

void PropagateDialog::acceptInput()
{
    if (GCFLine->value() + BCFLLine->value() > 1.0)
    {
        QMessageBox msg(QMessageBox::Information, "Input error", "BCLF Weight + GCF Weight must be <= 1.0", QMessageBox::NoButton, this);
        msg.exec();
    }
    else
        accept();
}

double PropagateDialog::getBLCF()
{
    return BCFLLine->value();
}

double PropagateDialog::getGCF()
{
    return GCFLine->value();
}

int PropagateDialog::getPasses()
{
    return passLine->value();
}
