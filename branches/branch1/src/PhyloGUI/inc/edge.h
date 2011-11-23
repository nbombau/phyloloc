#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include <Qt>
//#include "PhyloGUI/GuiAspect.h"
#include "Domain/INode.h"
#include "Phyloloc/Propagator/PropagatorAspect.h"
#include "Domain/LocationAspect.h"

namespace PhyloGUI
{

template<class T> class GuiAspect;
typedef GuiAspect< Propagation::PropagatorAspect< Locations::LocationAspect< Domain::Node> > > GuiNode;

class Edge : public QGraphicsItem
{
public:
    Edge(GuiNode* sourceNode, GuiNode* destNode);
    GuiNode* sourceNode() const;
    GuiNode* destNode() const;
    QColor getColor() const;
    void setColor(const QColor c);
    void setSelected(const bool s);
    bool isSelected() const;
    void setVisible(bool visible);
    void adjust();

    enum { Type = UserType + 2 };
    int type() const
    {
        return Type;
    }

protected:
    QRectF boundingRect() const;
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
