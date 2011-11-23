#ifndef PROPAGATEDIALOG_H
#define PROPAGATEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QSpinBox>

namespace PhyloGUI
{

class PropagateDialog : public QDialog
{
    Q_OBJECT

public:
    PropagateDialog(QWidget* parent = NULL);
    ~PropagateDialog();
    double getBCLF();
    double getGCF();
    int getPasses();
private:

    QLabel* BCFLLabel;
    QDoubleSpinBox* BCFLLine;

    QLabel* GCFLabel;
    QDoubleSpinBox* GCFLine;

    QLabel* passLabel;
    QSpinBox* passLine;

    QPushButton* propagateButton;
    QPushButton* cancelButton;

private slots:
    void acceptInput();
};

}

#endif // FILEDIALOG_H
