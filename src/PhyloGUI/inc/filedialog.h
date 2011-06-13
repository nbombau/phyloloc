#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include "Phylopp/DataSource/FilesInfo.h"

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    FileDialog(QWidget *parent=0);
    ~FileDialog();

    std::string getLocationsFile();
    std::string getDistancesFile();
    std::string getTreesFile();
private:
    QLabel* distancesLabel;
    QLineEdit *distancesLine;
    QPushButton *distancesButton;

    QLabel* locationsLabel;
    QLineEdit *locationsLine;
    QPushButton *locationsButton;

    QLabel* treesLabel;
    QLineEdit *treesLine;
    QPushButton *treesButton;

    QPushButton *loadButton;
    QPushButton *cancelButton;

private slots:
    void distancesButtonAction();
    void locationsButtonAction();
    void treesButtonAction();
    void loadButtonAction();
};

#endif // FILEDIALOG_H
