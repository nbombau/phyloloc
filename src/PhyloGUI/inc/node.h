#ifndef NODE_H
#define NODE_H

#include <QGraphicsItem>
#include <QList>

class Edge;
class GraphWidget;
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

namespace Ui {
    class Node;
}

class Node : public QGraphicsItem
{
public:
    Node(GraphWidget *graphWidget);

    void addEdge(Edge *edge);
    QList<Edge *> edges() const;

    enum { Type = UserType + 1 };
    int type() const { return Type; }

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool selected; //TODO: Pasar al aspecto

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    QList<Edge *> edgeList;
    QPointF newPos;
    GraphWidget *graph;

};

#endif

