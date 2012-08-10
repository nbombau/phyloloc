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
#ifndef PROPAGATEDIALOG_H
#define PROPAGATEDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QTextBoundaryFinder>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <string>

namespace PhyloGUI
{

class PropagateDialog : public QDialog
{

public:
    /**
    * Constructor. Returns a dialog for setting propagation parameters.
    *
    * @param parent dialog's parent widget.
    */
    PropagateDialog(QWidget* parent = NULL);

    /**
    * Destructor.
    */
    ~PropagateDialog();

    /**
    * Returns the branch length correction factor entered by the user.
    *
    * @return returns the branch length correction factor.
    */
    double getBLCF() const;

    /**
    * Returns the branch geographical factor entered by the user.
    *
    * @return returns the geographical correction factor.
    */
    double getGCF() const;

    /**
    * Returns the number of iterations for the propagation entered by the user.
    *
    * @return returns the number of iterations.
    */
    unsigned int getPasses() const;

    /**
    * Returns if the process should export deviations to a given file
    *
    * @return returns true if deviations of propagation process should be exported
    */
    bool getExportDeviations() const;

    /**
    * Returns the path where the propagation deviations should be exported
    *
    * @return returns file path where the propagation deviations should be exported
    */
    std::string getExportPath() const;

private:
    QLabel* BCFLLabel;
    QDoubleSpinBox* BCFLLine;

    QLabel* GCFLabel;
    QDoubleSpinBox* GCFLine;

    // Pass number was set to 2
    //QLabel* passLabel;
    //QSpinBox* passLine;

    QLabel* pathLabel;
    QLineEdit* pathLineEdit;
    QPushButton* selectPathButton;

    QCheckBox* exportDeviationCheckBox;

    QPushButton* propagateButton;
    QPushButton* cancelButton;

    static const unsigned int NUMBER_OF_PASSES = 2;

private slots:
    void acceptInput();
    void selectFile();
    void unlockPath(int);
};

}

#endif // FILEDIALOG_H
