#include <QFileDialog>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include "PhyloGUI/inc/propagatedialog.h"

PropagateDialog::PropagateDialog(QWidget* parent)
    : QDialog(parent)
{
    this->setBaseSize(450, 350);
    setFixedSize(baseSize());

    this->setWindowTitle("Propagation");
    const int leftMargin = 20;
    const int topMargin  = 20;
    const int labelWidth = 500;
    const int lineWidth  = 50;
    const int buttonWidth = 50;

    const int loadButtonWidth = 100;
    const int height = 25;
    int top = topMargin;

    top += height;

    BCFLLabel = new QLabel(this);
    BCFLLabel->setText("BCLF Weight (Number between 0 and 1):");
    BCFLLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;

    BCFLLine = new QLineEdit(this);
    BCFLLine->setGeometry(leftMargin, top, lineWidth, height);
    BCFLLine->setText("0.5");
    top += height + 5;

    BCFLerror = new QLabel(this);
    BCFLerror->setText("");
    BCFLerror->setGeometry(leftMargin, top, labelWidth, height);
    top += height;




    GCFLabel = new QLabel(this);
    GCFLabel->setText("GCF Weight (Number between 0 and 1):");
    GCFLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;

    GCFLine = new QLineEdit(this);
    GCFLine->setGeometry(leftMargin, top, lineWidth, height);
    GCFLine->setText("0.5");
    top += height + 5;

    GCFerror = new QLabel(this);
    GCFerror->setText("");
    GCFerror->setGeometry(leftMargin, top, labelWidth, height);
    top += height;






    passLabel = new QLabel(this);
    passLabel->setText("Number of passes:");
    passLabel->setGeometry(leftMargin, top, labelWidth, height);
    top += height;

    passLine = new QLineEdit(this);
    passLine->setGeometry(leftMargin, top, lineWidth, height);
    passLine->setText("1");
    top += height + 5;

    passerror = new QLabel(this);
    passerror->setText("");
    passerror->setGeometry(leftMargin, top, labelWidth, height);
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
    delete BCFLerror;
    delete BCFLLabel;
    delete BCFLLine;

    delete GCFerror;
    delete GCFLabel;
    delete GCFLine;

    delete passerror;
    delete passLabel;
    delete passLine;

    delete cancelButton;
    delete propagateButton;
}

void PropagateDialog::acceptInput()
{
    QIntValidator intValidator(this);
    intValidator.setBottom(0);
    intValidator.setTop(9999);
    QDoubleValidator doubleValidator(this);
    doubleValidator.setBottom(0);
    doubleValidator.setTop(1);
    bool error = false;
    int pos = 0;
    QString errorString;
    QString passInput = passLine->text();
    QString GCFinput = GCFLine->text();
    QString BCLFinput = BCFLLine->text();
    passerror->setText("");
    GCFerror->setText("");
    BCFLerror->setText("");

    if (intValidator.validate(passInput, pos) != QValidator::Acceptable)
    {
        error = true;
        passerror->setText("<font color='red'>The amount of passes must be a number between 0 and 9999</font>");
    }
    if (doubleValidator.validate(GCFinput, pos) != QValidator::Acceptable)
    {
        error = true;
        GCFerror->setText("<font color='red'>The GCF value must be a number between 0 and 1</font>");
    }
    if (doubleValidator.validate(BCLFinput, pos) != QValidator::Acceptable)
    {
        error = true;
        BCFLerror->setText("<font color='red'>The BCLF value must be a number between 0 and 1</font>");
    }

    if (!error)
    {
        accept();
    }
}

double PropagateDialog::getBCLF()
{
    return BCFLLine->text().toDouble();
}


double PropagateDialog::getGCF()
{
    return GCFLine->text().toDouble();
}

int PropagateDialog::getPasses()
{
    return passLine->text().toInt();
}
