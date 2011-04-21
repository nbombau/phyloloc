#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    setModal(true);
    setSizeGripEnabled(true);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

void OptionsDialog::accept(){

}
