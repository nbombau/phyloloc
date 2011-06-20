#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <stdlib.h>
#include <QFileDialog>
#include <stdio.h>
#include <QListWidgetItem>
#include "PhyloGUI/inc/graphwidget.h"
#include "Domain/ITreeCollection.h"
#include "Phylopp/DataSource/FileDataSource.h"
#include "Phylopp/DataSource/FilesInfo.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);

    ~MainWindow();


private:
    Ui::MainWindow* ui;
    GraphWidget* graph;
    ITree<GuiNode>* actualTree;
    void loadTree(const DataSource::FilesInfo& info);
    ITreeCollection<GuiNode> trees;

public slots:
    void drawTree();

private slots:
    void on_actionProcess_tree_triggered();
    void on_actionSelect_Ancestors_triggered();
    void on_actionSelect_descendants_triggered();
    void on_actionSelect_all_nodes_triggered();
    void on_actionClear_selection_triggered();
    void on_actionColor_nodes_triggered();
    void on_actionOptions_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionSearch_terminal_nodes_triggered();
};

#endif
