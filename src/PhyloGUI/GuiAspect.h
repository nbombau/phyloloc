#ifndef GUIASPECT_H
#define GUIASPECT_H

#include <string>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QColorDialog>
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

#include "PhyloGUI/inc/edge.h"
#include "Domain/INode.h"
#include "Phyloloc/Propagator/PropagatorAspect.h"
#include "Domain/LocationAspect.h"

namespace PhyloGUI
{
template <class T>
class GuiAspect : public T, public QGraphicsItem
{


private:
    bool selected;
    bool expanded;
    QColor color;
    QList<Edge*> edgeListFrom;
    QList<Edge*> edgeListTo;
    QGraphicsTextItem* graphicsName;

public:

    GuiAspect() : selected(false), expanded(true), color(Qt::yellow), graphicsName(NULL)
    {
        setCacheMode(DeviceCoordinateCache);
        setZValue(1000);
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

    void setGraphicsName(QGraphicsTextItem* graphicsName)
    {
        this->graphicsName = graphicsName;
    }

    bool hasGraphicsName() const
    {
        return graphicsName != NULL;
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
        qreal adjust = 0;
        QRectF rect(-10 - adjust, -10 - adjust,
                    20 + adjust, 20 + adjust);
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
        if(visible)
            this->setExpanded(visible);
        while (i.hasNext())
        {
            Edge* edge = i.next();
            edge->setVisible(visible);
        }
        if (hasGraphicsName())
            graphicsName->setVisible(visible);
    }

    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        QRect rect(-7, -7, 20, 20);

        QRadialGradient gradient(-3, -3, 10);

        if (isSelected())
            gradient.setColorAt(0, Qt::red);
        else
            gradient.setColorAt(0, color);

        painter->setBrush(gradient);
        painter->setPen(QPen(isExpanded() ? Qt::black : Qt::green, isExpanded() ? 0 : 3));
        rect = QRect(-7, -7, 20, 20);
        painter->drawEllipse(-10, -10, 20, 20);

        if (!this->probabilities.empty())
        {
            gradient.setColorAt(0,Qt::black);
            painter->setBrush(gradient);
            painter->setPen(QPen(Qt::black, 2));
            rect = QRect(-7, -7, 20, 20);
            painter->drawEllipse(-1, -1, 2, 2);
        }
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
            menu.addSeparator();
        }
        menu.addAction("Set color...");
        menu.addSeparator();
        if(!this->isLeaf())
            menu.addAction("Select descendants");
        menu.addAction("Select ancestors");
        menu.addSeparator();
        if(!isSelected())
            menu.addAction("Select node");
        else
            menu.addAction("Unselect node");
        QAction* a = menu.exec(event->screenPos());
        if (a != NULL)
        {
            if (a->text()=="Collapse" || a->text()=="Expand")
                expandCollapseAction();
            else if(a->text()=="Set color...")
                selectNodeColor();
            else if(a->text()=="Select ancestors")
                selectAncestors();
            else if(a->text()=="Select descendants")
                selectDescandants();
            else if(a->text()=="Select node" || a->text()=="Unselect node")
                setSelected(!isSelected());
            //else not needed

            this->update();
        }
    }

    void selectDescandants()
    {
        setSelected(true);
        QListIterator<Edge*> it(edgeListTo);
        while(it.hasNext())
            it.next()->selectDestNode();
        update();
    }

    void selectAncestors()
    {
        setSelected(true);
        if(!edgeListFrom.empty())
            edgeListFrom.first()->selectSourceNode();
        update();
    }

private:

    void selectNodeColor()
    {
        QColor color = QColorDialog::getColor();
        if (color.isValid())
            setColor(color);
    }

    void expandCollapseAction()
    {
        setExpanded(!isExpanded());
        QListIterator<Edge*> i(edgeListTo);

        while (i.hasNext())
        {
            Edge* edge = i.next();
            edge->setVisible(!edge->isVisible());

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

        if (!this->probabilities.empty())
        {
            description.append("\n\nPlausibility vector: [ ");
            for (unsigned int i = 0; i < this->probabilities.size(); i++)
            {
                description.append(QString().setNum(this->probabilities[i], 'f', 3));
                description.append(" ");
            }
            description.append(" ]");
        }

        QMessageBox msgBox(QMessageBox::Information
                           ,this->getName().empty()?"Node name not available":this->getName().c_str()
                           ,description, QMessageBox::NoButton
                           ,(QWidget *)scene()->parent()->parent()->parent()->parent());
        msgBox.exec();
    }


};

typedef GuiAspect< Propagation::PropagatorAspect< Locations::LocationAspect< Domain::Node> > > GuiNode;

}

#endif
