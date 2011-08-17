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
#include "Phyloloc/Propagator/PropagatorAspect.h"


namespace PhyloGUI
{

class NodeDetailDialog : public QDialog
{
    Q_OBJECT

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
                     Locations::LocationManager& locationManager,
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
