#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QtGui/QGraphicsView>
#include <math.h>
#include <QMouseEvent>
#include <queue>
#include <list>
#include <QSizePolicy>

#include "Domain/ITree.h"
#include "PhyloGUI/inc/edge.h"
#include "Domain/INode.h"
#include "Domain/ITree.h"
#include "PhyloGUI/GuiAspect.h"
using namespace Domain;
typedef GuiAspect< BaseAspect> GuiNode;






namespace Ui
{
class GraphWidget;
}

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget* parent = 0);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void paintNode(QColor color,ITree<GuiNode>* tree);
    void draw(ITree<GuiNode>* tree);
    void unSelectAllNodes(ITree<GuiNode>* tree);
    void selectAllNodes(ITree<GuiNode>* tree);
    void selectNodeDescendants(ITree<GuiNode>* tree);
    void selectNodeAncestors(ITree<GuiNode>*tree);

protected:
    void wheelEvent(QWheelEvent* event);
    void drawBackground(QPainter* painter, const QRectF& rect);
    void scaleView(qreal scaleFactor);
    void resizeEvent(QResizeEvent* event);

private:
    int timerId;
    void drawTree(QGraphicsScene* scene, GuiNode* node);
    QPointF drawTreeAux(QGraphicsScene* scene, GuiNode* node, float depth, unsigned int* leafNumber);
    void reScaleScene();
};

#endif
