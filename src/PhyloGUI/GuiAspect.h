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
#include <mili/mili.h>
#include <QObject>
#include <QList>
#include <list>
#include <QGraphicsSceneContextMenuEvent>
#include <QContextMenuEvent>
#include <QMessageBox>
#include <QGraphicsItem>

#include "PhyloGUI/inc/graphwidget.h"
#include "PhyloGUI/inc/edge.h"
#include "Domain/INode.h"
#include "Phyloloc/Propagator/PropagatorAspect.h"

namespace PhyloGUI
{

using namespace std;
class Edge;

template <class T>
class GuiAspect : public T, public QGraphicsItem
{

private:
    bool selected;
    bool expanded;
    QColor color;
    QList<Edge*> edgeListFrom;
    QList<Edge*> edgeListTo;

public:

    GuiAspect() : selected(false), expanded(true), color(Qt::yellow)
    {
        setCacheMode(DeviceCoordinateCache);
    }

    ~GuiAspect()
    {
        /*
        for (QList<Edge*>::Iterator it = edgeListTo.begin(); it != edgeListTo.end(); ++it)
        {
            delete *it;
        }
        */
    }

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

    void addEdgeFrom(Edge* edge)
    {
        edgeListFrom.push_back(edge);
    }

    QList<Edge*> edgesFrom() const
    {
        return edgeListFrom;
    }

    void addEdgeTo(Edge* edge)
    {
        edgeListTo.push_front(edge);
    }

    QList<Edge*> edgesTo() const
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
    void setVisible(bool visible)
    {
        QGraphicsItem::setVisible(visible);
        QListIterator<Edge*> i(edgeListTo);
        while (i.hasNext())
        {
            /*Edge* edge =*/ i.next();
            //edge->setVisible(visible);
            //edge->adjust();
        }
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        QRect rect(-7, -7, 20, 20);
        //painter->setPen(Qt::NoPen);
        //painter->setBrush(Qt::darkGray);
        //painter->drawEllipse(rect);

        QRadialGradient gradient(-3, -3, 10);

        if (isSelected())
        {
            gradient.setColorAt(0, Qt::red);
        }
        else if (!isSelected())
        {
            gradient.setColorAt(0, color);
        }
        painter->setBrush(gradient);
        painter->setPen(QPen(Qt::black, 0));
        rect = QRect(-7, -7, 20, 20);
        painter->drawEllipse(-10, -10, 20, 20);
    }

    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event)
    {
        Q_UNUSED(event);
        QMenu menu;
        if (!this->isLeaf())
        {
            if (this->isExpanded())
                menu.addAction("Collapse");
            else
                menu.addAction("Expand");

            QAction* a = menu.exec(event->screenPos());
            if (a != NULL)
            {
                if (a->text().compare("Collapse") || a->text().compare("Expand"))
                {
                    QListIterator<Edge*> i(edgeListTo);

                    while (i.hasNext())
                    {
                        /*Edge* edge = */i.next();
                        //edge->setVisible(!edge->isVisible());
                    }
                }
            }
        }
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
    }

    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
    {
        Q_UNUSED(event);
        QString description = QString::fromAscii("Name: ");
        if (this->getName().empty())
            description.append("No information available.");
        else
            description.append(this->getName().c_str());

        description.append("\n\nLocation: ");
        if (this->getLocation().empty())
            description.append("No information available.");
        else
            description.append(this->getLocation().c_str());

        if (this->probabilities.size() != 0)
        {
            description.append("\n\nProbabilities vector: [ ");
            for (unsigned int i = 0; i < this->probabilities.size(); i++)
            {
                description.append(QString().setNum(this->probabilities[i]));
                description.append(" ");
            }
            description.append(" ]");
        }

        QMessageBox msgBox;
        msgBox.setText(description);
        msgBox.exec();
    }


};

}

#endif
