#include <QPainter>

#include "PhyloGUI/GuiAspect.h"
#include "PhyloGUI/inc/edge.h"

using namespace PhyloGUI;

Edge::Edge(GuiNode* sourceNode, GuiNode* destNode)
    : color(Qt::black), selected(false)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    setZValue(-1000);
    sourcePoint = source->pos();
    destPoint = dest->pos();
    //adjust();
}

GuiNode* Edge::sourceNode() const
{
    return source;
}

GuiNode* Edge::destNode() const
{
    return dest;
}

QColor Edge::getColor() const
{
    return color;
}
void Edge::setColor(const QColor c)
{
    color = c;
}
void Edge::setSelected(const bool s)
{
    selected = s;
}
bool Edge::isSelected() const
{
    return selected;
}
void Edge::setVisible(bool visible)
{
    QGraphicsItem::setVisible(visible);
    dest->setVisible(visible);
}
void Edge::adjust()
{
    if (source != NULL && dest != NULL)
    {
        QLineF line(mapFromItem(source, 0, 0), mapFromItem(dest, 0, 0));
        qreal length = line.length();

        prepareGeometryChange();

        if (length > qreal(20.))
        {
            QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
            sourcePoint = line.p1() + edgeOffset;
            destPoint = line.p2() - edgeOffset;
        }
        else
            sourcePoint = destPoint = line.p1();
    }
}

QRectF Edge::boundingRect() const
{
    QRectF rect;
    if (source == NULL || dest == NULL)
    {
        rect = QRectF();
    }
    else
    {
        rect = QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                          destPoint.y() - sourcePoint.y()))
               .normalized();
    }
    return rect;
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (source != NULL && dest != NULL)
    {
        /*
         * If the edge is selected, the z-value is set to 0. That way if
         * multiple edges are stacked the visibility of the one selected
         * is ensured.
         */
        if (selected)
            this->setZValue(0);
        else
            this->setZValue(-1000);

        //Union between the two parts of the line
        QPointF point(destPoint.x(), sourcePoint.y());

        // Draw the horizontal part of the line
        QLineF line(sourcePoint, point);
        painter->setPen(QPen(selected ? Qt::red : color, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);

        // Draw the vertical part of the line
        line.setPoints(point, destPoint);
        painter->setPen(QPen(selected ? Qt::red : color, 6, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);
    }
}

void Edge::selectSourceNode()
{
    setSelected(true);
    if (source != NULL)
        sourceNode()->selectAncestors();
    update();
}

void Edge::selectDestNode()
{
    setSelected(true);
    if (dest != NULL)
        destNode()->selectDescandants();
    update();
}
