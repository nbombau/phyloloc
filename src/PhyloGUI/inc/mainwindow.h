#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <stdlib.h>
#include <QFileDialog.h>
#include <stdio.h>
#include <QListWidgetItem>
#include "graphwidget.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GraphWidget * graph;

private slots:
    void on_actionColor_nodes_triggered();
    void on_actionExport_to_PNG_triggered();
    void on_listWidget_itemDoubleClicked(QListWidgetItem* item);
    void on_actionOptions_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
};

#endif // MAINWINDOW_H