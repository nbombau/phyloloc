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
#include <QDoubleSpinBox>
#include <QSpinBox>

namespace PhyloGUI
{

class PropagateDialog : public QDialog
{
    Q_OBJECT

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
    double getBLCF();

    /**
    * Returns the branch geographical factor entered by the user.
    *
    * @return returns the geographical correction factor.
    */
    double getGCF();

    /**
    * Returns the number of iterations for the propagation entered by the user.
    *
    * @return returns the number of iterations.
    */
    int getPasses();
private:
    QLabel* BCFLLabel;
    QDoubleSpinBox* BCFLLine;

    QLabel* GCFLabel;
    QDoubleSpinBox* GCFLine;

    // Pass number was set to 2
    //QLabel* passLabel;
    //QSpinBox* passLine;

    QPushButton* propagateButton;
    QPushButton* cancelButton;

    static const int passesNumber = 2;

private slots:
    void acceptInput();
};

}

#endif // FILEDIALOG_H
