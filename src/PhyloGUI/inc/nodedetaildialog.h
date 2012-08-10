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
#ifndef NODEDETAILDIALOG_H
#define NODEDETAILDIALOG_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTableWidget>
#include "phyloloc/Propagator/PropagatorAspect.h"
#include "phyloloc/Propagator/StatisticsAspect.h"


namespace PhyloGUI
{

class NodeDetailDialog : public QDialog
{

public:
    /**
    * Constructor. Returns a dialog displaying the node's information.
    *
    * @param name the node's name.
    * @param locations the node's location.
    * @param probabilities the node's probabilities vector after propagation.
    * @param locationManager the location manager to map the propabilities with
    * a location.
    * @param parent dialog's parent widget.
    */
    NodeDetailDialog(Domain::NodeName& name,
                     Locations::Location& locations,
                     Propagation::LocationProbabilities& probabilities,
                     Locations::LocationManager* locationManager,
                     const Propagation::StatisticInfoVector& statistics,
                     QWidget* parent = NULL);

    /**
    * Destructor.
    */
    ~NodeDetailDialog();
private:
    QLabel* nameLabel;
    QLabel* locationLabel;
    QLabel* nameText;
    QLabel* locationText;
    QTableWidget* propGrid;
    QTableWidget* consGrid;
    QPushButton* propagateButton;

};

}

#endif // FILEDIALOG_H
