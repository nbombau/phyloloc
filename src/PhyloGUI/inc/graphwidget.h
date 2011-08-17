#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>
#include <math.h>
#include <QMouseEvent>
#include <queue>
#include <list>
#include <QSizePolicy>
#include <QSize>
#include <QGraphicsTextItem>

#include "Domain/ITree.h"
#include "Domain/INode.h"
#include "Domain/ITreeCollection.h"
#include "PhyloGUI/GuiAspect.h"
#include "Phyloloc/Propagator/PropagatorAspect.h"
#include "Domain/LocationAspect.h"
#include "Domain/LocationManager.h"

namespace PhyloGUI
{

class GraphWidget : public QGraphicsView
{

public:
    GraphWidget(Locations::LocationManager& locationManager,QWidget* parent = 0);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paintNode(QColor color, Domain::ITree<GuiNode>* tree);
    void draw(Domain::ITree<GuiNode>* tree);
    void draw(void);
    void unSelectAllNodes(Domain::ITree<GuiNode>* tree);
    void selectAllNodes(Domain::ITree<GuiNode>* tree);
    void selectNodeDescendants(Domain::ITree<GuiNode>* tree);
    void selectNodeAncestors(Domain::ITree<GuiNode>*tree);
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
