#include <QPainter>

#include "PhyloGUI/inc/edge.h"

Edge::Edge(GuiNode* sourceNode, GuiNode* destNode)
    : color(Qt::black), selected(false)
{
    setAcceptedMouseButtons(0);
    source = sourceNode;
    dest = destNode;
    setZValue(-1);
    adjust();
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
        {
            sourcePoint = destPoint = line.p1();
        }
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
        //qreal penWidth = 1;
        rect = QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                          destPoint.y() - sourcePoint.y()))
               .normalized();
        /*qreal extra = (penWidth + arrowSize) / 2.0;
        rect = QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                          destPoint.y() - sourcePoint.y()))
               .normalized()
               .adjusted(-extra, -extra, extra, extra);*/
    }
    return rect;
}

void Edge::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    if (source != NULL && dest != NULL)
    {
        //Union between the two parts of the line
        QPointF point(destPoint.x(), sourcePoint.y());

        // Draw the horizontal part of the line
        QLineF line(sourcePoint, point);
        painter->setPen(QPen(selected ? Qt::red : color, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);

        // Draw the vertical part of the line
        line.setPoints(point, destPoint);
        painter->setPen(QPen(selected ? Qt::red : color, 7, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter->drawLine(line);
    }
}

