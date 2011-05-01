#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <Qt>
#include <QRectF>
#include <stdio.h>

#include "PhyloGUI/inc/edge.h"
#include "PhyloGUI/inc/node.h"
#include "PhyloGUI/inc/graphwidget.h"

Node::Node(GraphWidget* graphWidget)
    : graph(graphWidget)
{
    setCacheMode(DeviceCoordinateCache);
    setZValue(-1);
    selected = false;
}

void Node::addEdge(Edge* edge)
{
    edgeList << edge;
    edge->adjust();
}

QList<Edge*> Node::edges() const
{
    return edgeList;
}

QRectF Node::boundingRect() const
{
    qreal adjust = 2;
    return QRectF(-10 - adjust, -10 - adjust,
                  23 + adjust, 23 + adjust);
}

QPainterPath Node::shape() const
{
    QPainterPath path;
    path.addEllipse(-10, -10, 20, 20);
    return path;
}

void Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget*)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);

    if (selected == true)
    {
        gradient.setColorAt(0, Qt::red);
    }
    else if (!selected)
    {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
    this->y() + 20;
}

void Node::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->modifiers() == Qt::SHIFT)
    {
        if (this->isUnderMouse())
        {
            this->selected = !this->selected;
            this->update();
        }
    }
    else
        printf("detalles");
}

