#ifndef GUIASPECT_H
#define GUIASPECT_H

#include <string>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOption>
#include <QTimer>
#include <Qt>
#include <QMenu>
#include <QAction>
#include <QRectF>
#include <stdio.h>
#include "../Domain/INode.h"
//#include "inc/graphwidget.h"
//#include "inc/edge.h"
#include "inc/graphwidget.h"
#include <QObject>
#include <QList>
#include <list>
#include <QGraphicsSceneContextMenuEvent>
#include <QContextMenuEvent>



namespace Ui
{
class GuiAspect;
}

class Edge;
using namespace std;

template <class T>
class GuiAspect : public Domain::Node<GuiAspect<T> >, public QGraphicsItem
{
public:
    /*enum { Type = UserType + 1 };
    int type() const { return Type; }*/

    GuiAspect() : selected(false), expanded(true),color(Qt::yellow)
    {
        setCacheMode(DeviceCoordinateCache);
        setZValue(-1);
    }

    ~GuiAspect() {}

        
        /*GuiAspect(const Location l, const NodeName n, const BranchLength b)
        : Domain::Node<GuiAspect<T> > (l, n, b) {}*/

    bool isSelected() const
    {
        return selected;
    }

    bool isExpanded() const
    {
        return expanded;
    }

    QColor getColor() const
    {
        return color;
    }

    void setSelected(const bool s)
    {
        selected = s;
    }

    void setExpanded(const bool e)
    {
        expanded = e;
    }

    void setColor(const QColor c)
    {
        color = c;
    }

    void addEdgeFrom(Edge *edge)
     {
         edgeListFrom.push_back(edge);
     }

     QList<Edge *> edgesFrom() const
     {
         return edgeListFrom;
     }

     void addEdgeTo(Edge *edge)
      {
          edgeListTo.push_front(edge);
      }

      QList<Edge *> edgesTo() const
      {
          return edgeListTo;
      }

    QRectF boundingRect() const
    {
        qreal adjust = 2;
        QRectF rect(-10 - adjust, -10 - adjust,
                      23 + adjust, 23 + adjust);
        return rect;
    }

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(-10, -10, 20, 20);
        return path;
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setPen(Qt::NoPen);
        painter->setBrush(Qt::darkGray);
        painter->drawEllipse(-7, -7, 20, 20);

        QRadialGradient gradient(-3, -3, 10);

        if (isSelected())
        {
            gradient.setColorAt(0, Qt::red);
        }
        else if (!isSelected())
        {
            gradient.setColorAt(0, color);
            //gradient.setColorAt(1, Qt::darkYellow);
        }
        painter->setBrush(gradient);
        painter->setPen(QPen(Qt::black, 0));
        painter->drawEllipse(-10, -10, 20, 20);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event)
    {
        if (event->modifiers() == Qt::SHIFT)
        {
            if (isUnderMouse())
            {
                setSelected(!isSelected());
                update();
            }
        }
        else if (event->modifiers() == Qt::CTRL)
        {
            if (isUnderMouse())
            {
                setExpanded(!isExpanded());
                update();
            }
        }
        else
            printf("detalles");
    }

private:
    bool selected;
    bool expanded;
    QColor color;
    QList<Edge *> edgeListFrom;
    QList<Edge *> edgeListTo;
    //QPointF newPos;
    //GraphWidget *graph;
};


#endif
