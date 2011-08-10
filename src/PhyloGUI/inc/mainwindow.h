#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <stdlib.h>
#include <QFileDialog>
#include <stdio.h>
#include <QListWidgetItem>
#include <fenv.h>

#include "PhyloGUI/inc/graphwidget.h"
#include "Domain/ITreeCollection.h"
#include "Phylopp/DataSource/FileDataSource.h"
#include "Phylopp/DataSource/FilesInfo.h"
#include "Phyloloc/Propagator/Propagator.h"
#include "Domain/ITree.h"

namespace Ui
{
class MainWindow;
}

namespace PhyloGUI
{

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = NULL);
    ~MainWindow();
    void activateMenuItems(bool activate);

    static void propagate(Domain::ITree<PhyloGUI::GuiNode>* tree,
                          unsigned int passesCount,
                          double geographicFactorWeight,
                          double branchLengthFactorWeight)
    {
        //sets rounded mode towards zero, so that convertion from double to float does not bring errors in propagation arguments
        int defaultRoundingMode = setRoundingMode(FE_TOWARDZERO);

        Propagation::Propagator<GuiNode>::propagate(tree, passesCount, geographicFactorWeight, branchLengthFactorWeight);

        setRoundingMode(defaultRoundingMode);
    }

private:
    Ui::MainWindow* ui;
    PhyloGUI::GraphWidget* graph;
    Domain::ITree<PhyloGUI::GuiNode>* actualTree;
    void loadTree(const DataSource::FilesInfo& info, bool allowMissingData);
    Domain::ITreeCollection<PhyloGUI::GuiNode> trees;

    static int setRoundingMode(int roundingMode)
    {
        return fesetround(roundingMode);
    }

public slots:
    void drawTree();
    //void nodeSelected(int nodeAction);

private slots:
    void on_actionProcess_tree_triggered();
    void on_actionSelect_Ancestors_triggered();
    void on_actionSelect_descendants_triggered();
    void on_actionSelect_all_nodes_triggered();
    void on_actionClear_selection_triggered();
    void on_actionColor_nodes_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionSearch_terminal_nodes_triggered();
    void on_actionZoom_triggered();
    void on_actionZoom_2_triggered();
};

}
#endif
