#include "graphwidget.h"
#include "edge.h"
#include "node.h"
#include <QSizePolicy>
#include <QtGui>

#include <math.h>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent)
{
    //Properties
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);
    resize(parentWidget()->width(),parentWidget()->height());
}

void GraphWidget::wheelEvent(QWheelEvent *event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    Q_UNUSED(painter);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void GraphWidget::draw()
{
    QGraphicsScene *scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //Uncomment to set the fixed size for the cambas.
    scene->setSceneRect(-50, -50, 180, 180);
    //scale(qreal(0.005), qreal(0.005));
    //scene->setSceneRect(-200, -200, 1000, 1000);
    //TODO test with a big cambas!!!
    //scene->setSceneRect(-200, -200, 5000, 5000);

    Node *node1 = new Node(this);
    Node *node2 = new Node(this);
    Node *node3 = new Node(this);
    Node *node4 = new Node(this);
    centerNode = new Node(this);
    Node *node6 = new Node(this);
    Node *node7 = new Node(this);
    Node *node8 = new Node(this);
    Node *node9 = new Node(this);

    node1->setPos(-50, -50);
    node2->setPos(0, -50);
    node3->setPos(50, -50);
    node4->setPos(-50, 0);
    centerNode->setPos(0, 0);
    node6->setPos(50, 0);
    node7->setPos(-50, 50);
    node8->setPos(0, 50);
    node9->setPos(50, 50);

    scene->addItem(node1);
    scene->addItem(node2);
    scene->addItem(node3);
    scene->addItem(node4);
    scene->addItem(centerNode);
    scene->addItem(node6);
    scene->addItem(node7);
    scene->addItem(node8);
    scene->addItem(node9);
    scene->addItem(new Edge(node1, node2));
    scene->addItem(new Edge(node2, node3));
    scene->addItem(new Edge(node2, centerNode));
    scene->addItem(new Edge(node3, node6));
    scene->addItem(new Edge(node4, node1));
    scene->addItem(new Edge(node4, centerNode));
    scene->addItem(new Edge(centerNode, node6));
    scene->addItem(new Edge(centerNode, node8));
    scene->addItem(new Edge(node6, node9));
    scene->addItem(new Edge(node7, node4));
    scene->addItem(new Edge(node8, node7));
    scene->addItem(new Edge(node9, node8));

    setScene(scene);
    reScaleScene();
}

void GraphWidget::resizeEvent ( QResizeEvent * event )
{
    resize(parentWidget()->width(),parentWidget()->height());
    //reScaleScene();
}

void GraphWidget::reScaleScene()
{
    if(this->scene()->width()>this->scene()->height())
    {
        if(this->scene()->width()>this->parentWidget()->width()){
            printf("1\n");
            scale(qreal(this->scene()->width()/this->parentWidget()->width()),qreal(this->scene()->width()/this->parentWidget()->width()));
        }else{
            printf("2\n");
            scale(qreal(this->parentWidget()->width()/this->scene()->width()),qreal(this->parentWidget()->width()/this->scene()->width()));
        }
    } else {
        if(this->scene()->height()>this->parentWidget()->height()){
            printf("3\n");
            scale(qreal(this->scene()->height()/this->parentWidget()->height()),qreal(this->scene()->height()/this->parentWidget()->height()));
        } else {
            printf("4\n");
            scale(qreal(this->parentWidget()->height()/this->scene()->height()),qreal(this->parentWidget()->height()/this->scene()->height()));
        }
    }
}
