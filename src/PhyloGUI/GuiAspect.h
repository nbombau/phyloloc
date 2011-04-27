#ifndef GUIASPECT_H
#define GUIASPECT_H

#include <string>
//#include <QGraphicsScene>
//#include <QGraphicsSceneMouseEvent>
//#include <QPainter>
//#include <QStyleOption>
//#include <QTimer>
//#include <Qt>
//#include <QRectF>
#include <stdio.h>
#include "../Domain/INode.h"
//#include "inc/graphwidget.h"
//#include "inc/edge.h"

namespace PhyloGui
{
    template <class T>
    class GuiAspect : public Domain::Node<GuiAspect<T> >//,public QGraphicsItem
    {
    public:

        GuiAspect() : selected(false), expanded(true){}/*, graph(graphWidget)
        {
            setCacheMode(DeviceCoordinateCache);
            setZValue(-1);
            selected=false;
        }*/

        ~GuiAspect() {}

        bool isSelected() const
        {
            return selected;
        }

        bool isExpanded() const
        {
            return expanded;
        }

        std::string getColor() const
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

        void getColor(const std::string c)
        {
            color = c;
        }
    /*protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event)
        {
            if(event->modifiers()==Qt::SHIFT){
                if(this->isUnderMouse()){
                    this->selected=!this->selected;
                    this->update();
                }
            }
            else
                printf("detalles");
        }


        void addEdge(Edge *edge)
        {
            edgeList << edge;
            edge->adjust();
        }

        enum { Type = UserType + 1 };
        int type() const { return Type; }

        QList<Edge *> edges() const
        {
            return edgeList;
        }

        QRectF boundingRect() const
        {
            qreal adjust = 2;
            return QRectF(-10 - adjust, -10 - adjust,
                          23 + adjust, 23 + adjust);
        }

        QPainterPath shape() const
        {
            QPainterPath path;
            path.addEllipse(-10, -10, 20, 20);
            return path;
        }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
        {
            painter->setPen(Qt::NoPen);
            painter->setBrush(Qt::darkGray);
            painter->drawEllipse(-7, -7, 20, 20);

            QRadialGradient gradient(-3, -3, 10);

            if(selected==true){
                gradient.setColorAt(0, Qt::red);
            } else if(!selected) {
                gradient.setColorAt(0, Qt::yellow);
                gradient.setColorAt(1, Qt::darkYellow);
            }
            painter->setBrush(gradient);
            painter->setPen(QPen(Qt::black, 0));
            painter->drawEllipse(-10, -10, 20, 20);
            this->y()+20;
        }

        void mousePressEvent(QGraphicsSceneMouseEvent *event)
        {
            if(event->modifiers()==Qt::SHIFT){
                if(this->isUnderMouse()){
                    this->selected=!this->selected;
                    this->update();
                }
            }
            else
                printf("detalles");
        }*/



    private:
        bool selected;
        bool expanded;
        std::string color;
        /*QList<Edge *> edgeList;
        QPointF newPos;
        GraphWidget *graph;*/
    };
}

#endif
