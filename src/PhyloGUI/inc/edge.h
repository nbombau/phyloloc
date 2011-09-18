#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <Qt>
//#include "PhyloGUI/inc/graphwidget.h"
//#include "Domain/INode.h"
//#include "PhyloGUI/GuiAspect.h"
#include "Phyloloc/Propagator/PropagatorAspect.h"
#include "Domain/LocationAspect.h"
#include "Phyloloc/Propagator/StatisticsAspect.h"
#include "Phylopp/Consensor/ConsensorAspect.h"

namespace PhyloGUI
{

template<class T> class GuiAspect;
typedef GuiAspect<Propagation::StatisticAspect<Consensus::ConsensorAspect<Propagation::PropagatorAspect< Locations::LocationAspect< Domain::Node> > > > >  GuiNode;
class Edge : public QGraphicsItem
{
public:
    /**
    * Constructor. Creates an edge between de source node (the parent node) and
    * destination node (child node).
    *
    * @param sourceNode the parent node.
    * @param destNode the child node.
    */
    Edge(GuiNode* sourceNode, GuiNode* destNode);

    /**
    * Returns the node acting as the parent node.
    *
    * @returns the source node of the edge.
    */
    GuiNode* sourceNode() const;

    /**
    * Returns the node acting as the child node.
    *
    * @returns the destination node of the edge.
    */
    GuiNode* destNode() const;

    /**
    * Returns the color of the edge.
    *
    * @returns color of the edge.
    */
    QColor getColor() const;

    /**
    * Set's the color of the edge.
    *
    * @param c color of the edge.
    */
    void setColor(const QColor c);

    /**
    * Set if the edge is selected or not.
    *
    * @param s true or false.
    */
    void setSelected(const bool s);

    /**
    * Returns if the edge has been selected or not.
    *
    * @return true or false.
    */
    bool isSelected() const;

    /**
    * Set's if the edge is visible or not. If it is not visible the edge won't
    * be painted.
    *
    * @param visible true or false.
    */
    void setVisible(bool visible);

    /**
    * @deprecated This method is no longer in use. Kept just in case.
    */
    void adjust();

    /**
    * Sets the source node as selected.
    */
    void selectSourceNode();

    /**
    * Sets the destination node as selected.
    */
    void selectDestNode();

protected:
    /**
    * Defines the outer bounds of the item as a rectangle, all painting must be
    * restricted to inside an item's bounding rect.
    *
    * @return rectangle representing de bounding rectangle.
    */
    QRectF boundingRect() const;

    /**
    * Performs the actual painting of the edge.
    * The painter parameter performs low-level painting on widgets and other
    * paint devices.
    * The option parameter provides style options for the item, such as its
    * state, exposed area and its level-of-detail hints.
    * The widget argument is optional. If provided, it points to the widget
    * that is being painted on; otherwise, it is 0. For cached painting, widget
    * is always 0.
    *
    * @param painter
    * @param option
    * @param widget
    */
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);

private:
    GuiNode* source, *dest;
    QColor color;
    QPointF sourcePoint;
    QPointF destPoint;
    bool selected;
};

}

#endif
