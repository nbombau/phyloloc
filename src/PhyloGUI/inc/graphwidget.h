/*
 C o*pyright (C) 2011 Emmanuel Teisaire, Nicolás Bombau, Carlos Castro, Damián Domé, FuDePAN

 This file is part of the Phyloloc project.

 Phyloloc is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 Phyloloc is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Phyloloc.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <math.h>
#include <queue>
#include <list>
#include <QtGui/QGraphicsView>
#include <QMouseEvent>
#include <QSizePolicy>
#include <QSize>
#include <QGraphicsTextItem>

#include "phylopp/Domain/ITree.h"
#include "phylopp/Domain/INode.h"
#include "phylopp/Domain/ITreeCollection.h"
#include "phylopp/Domain/LocationAspect.h"
#include "phylopp/Domain/LocationManager.h"
#include "phyloloc/Propagator/PropagatorAspect.h"
#include "GuiAspect.h"

namespace PhyloGUI
{

class GraphWidget : public QGraphicsView
{

public:
    GraphWidget(Locations::LocationManager& locationManager, QWidget* parent = 0);
    ~GraphWidget();
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paintNode(QColor color, Domain::ITree<GuiNode>* tree);
    void draw(Domain::ITree<GuiNode>* tree);
    void draw(void);
    void unSelectAllNodes(Domain::ITree<GuiNode>* tree);
    void selectAllNodes(Domain::ITree<GuiNode>* tree);
    void selectNodeDescendants(Domain::ITree<GuiNode>* tree);
    void selectNodeAncestors(Domain::ITree<GuiNode>* tree);
    void clearNodeColoring(Domain::ITree<GuiNode>* tree);
    void scaleView(qreal scaleFactor);
    Locations::LocationManager& getLocationManager() const;
    QSize sizeHint() const;

protected:
    void wheelEvent(QWheelEvent* event);
    void drawBackground(QPainter* painter, const QRectF& rect);
    void resizeEvent(QResizeEvent* event);

private:
    Domain::ITree<GuiNode>* tree;
    int timerId;
    Locations::LocationManager& lm;
    void drawTree(QGraphicsScene* scene, GuiNode* node);
    QPointF drawTreeAux(QGraphicsScene* scene, GuiNode* node, float depth, unsigned int* leafNumber);
    void reScaleScene();
};

}

#endif
