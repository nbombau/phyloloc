#ifndef EDGE_H
#define EDGE_H

#include <QGraphicsItem>
#include "graphwidget.h"

#include "../../Domain/INode.h"
#include "PhyloGUI/GuiAspect.h"
using namespace Domain;
typedef GuiAspect< BaseAspect> GuiNode;

namespace Ui
{
class Edge;
}

//class Node;


class Edge : public QGraphicsItem
{
public:
    Edge(GuiNode* sourceNode, GuiNode* destNode);

    GuiNode* sourceNode() const;
    GuiNode* destNode() const;
    QColor getColor() const;
    void setColor(const QColor c);
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
    qreal arrowSize;
};

#endif
