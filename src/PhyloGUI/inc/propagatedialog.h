#ifndef PROPAGATEDIALOG_H
#define PROPAGATEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>

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
    QLabel* BCFLerror;
    QLabel* BCFLLabel;
    QLineEdit* BCFLLine;

    QLabel * GCFerror;
    QLabel* GCFLabel;
    QLineEdit* GCFLine;

    QLabel * passerror;
    QLabel* passLabel;
    QLineEdit* passLine;

    QPushButton* propagateButton;
    QPushButton* cancelButton;
    
private slots:
    void acceptInput();
};

#endif // FILEDIALOG_H
