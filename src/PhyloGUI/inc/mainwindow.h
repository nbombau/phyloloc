/*
    Copyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

    This file is part of the Phyloloc project.

    Phyloloc is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Phyloloc is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include <stdlib.h>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QList>

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

private:
    Ui::MainWindow* ui;
    PhyloGUI::GraphWidget* graph;
    Domain::ITree<PhyloGUI::GuiNode>* actualTree;
    void loadTree(const DataSource::FilesInfo& info, bool allowMissingData, LocationManager& locationManager);
    Domain::ITreeCollection<PhyloGUI::GuiNode> trees;
    Domain::ITree<PhyloGUI::GuiNode>* consensedTree;
    Locations::LocationManager locationManager;
    int consensedTreeRow;

public slots:
    void drawTree();

private slots:
    void on_actionClose_all_triggered();
    void on_actionActual_size_triggered();
    void on_actionProcess_tree_triggered();
    void on_actionSelect_Ancestors_triggered();
    void on_actionSelect_descendants_triggered();
    void on_actionSelect_all_nodes_triggered();
    void on_actionClear_selection_triggered();
    void on_actionColor_nodes_triggered();
    void on_actionSave_As_triggered();
    void on_actionOpen_triggered();
    void on_actionQuit_triggered();
    void on_actionAbout_triggered();
    void on_actionSearch_terminal_nodes_triggered();
    void on_actionZoom_triggered();
    void on_actionZoom_2_triggered();
};

}
#endif
