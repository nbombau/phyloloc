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
#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialog>
#include "Phylopp/DataSource/FilesInfo.h"

namespace PhyloGUI
{

class FileDialog : public QDialog
{
    Q_OBJECT

public:
    FileDialog(QWidget* parent = NULL);
    ~FileDialog();

    std::string getLocationsFile() const;
    std::string getDistancesFile() const;
    std::string getTreesFile() const;
    bool isMissingDataCheckBoxChecked() const;
private:
    QLabel* distancesLabel;
    QLineEdit* distancesLine;
    QPushButton* distancesButton;

    QLabel* locationsLabel;
    QLineEdit* locationsLine;
    QPushButton* locationsButton;

    QLabel* treesLabel;
    QLineEdit* treesLine;
    QPushButton* treesButton;

    QPushButton* loadButton;
    QPushButton* cancelButton;
    QCheckBox* missingDataCheckBox;

private slots:
    void distancesButtonAction();
    void locationsButtonAction();
    void treesButtonAction();
    void loadButtonAction();
};

}

#endif // FILEDIALOG_H
