#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>

namespace PhyloGUI
{

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = NULL);
    ~AboutDialog();

private:
    QLabel* nameLabel;
    QLabel* logoFudepanLabel;
    QLabel* logoItbaLabel;
    QLabel* logoEfpuLabel;
    QLabel* logoGplLabel;
    QPushButton* okButton;
private slots:
    void okButtonAction();

};

}

#endif // ABOUTDIALOG_H
