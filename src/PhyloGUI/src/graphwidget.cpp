#include "PhyloGUI/inc/graphwidget.h"
#include "Phylopp/Traversal/NodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

using namespace Traversal;
using namespace Domain;
using namespace std;
using namespace PhyloGUI;


struct AlwaysTruePredicate
{
    bool operator()(GuiNode*) const
    {
        return true;
    }
};

struct IsSelectedPredicate
{
    bool operator()(GuiNode* node) const
    {
        return node->isSelected();
    }
};

class ColorAction
{
public:
    ColorAction(QColor c)
    {
        color = c;
    }

    VisitAction visitNode(GuiNode* n)
    {
        n->setColor(color);
        n->setSelected(false);
        n->update();

        return ContinueTraversing;
    }

private:
    QColor color;
};

class ClearColorAction
{
public:
    VisitAction visitNode(GuiNode* n)
    {
        n->clearColor();
        n->update();
        return ContinueTraversing;
    }
};

class SelectAction
{
public:
    VisitAction visitNode(GuiNode* n)
    {
        n->setSelected(true);
        n->update();

        return ContinueTraversing;
    }
};

class UnSelectAction
{
public:
    VisitAction visitNode(GuiNode* n)
    {
        n->setSelected(false);
        n->update();
        Edge* edge;
        QList<Edge*> edgesTo = n->edgesTo();
        const unsigned int size = edgesTo.count();
        for (unsigned int i = 0; i < size; i++)
        {
            edge = edgesTo.at(i);
            edge->setSelected(false);
            edge->update();
        }

        return ContinueTraversing;
    }
};

class SelectDescendantsAction
{
public:
    VisitAction visitNode(GuiNode* n)
    {
        QList<Edge*> edgesFrom = n->edgesFrom();
        Edge* edge;
        if (n->isSelected() || (!edgesFrom.isEmpty() && edgesFrom.at(0) != NULL && edgesFrom.at(0)->isSelected()))
        {
            n->setSelected(true);
            n->update();
            QList<Edge*> edgesTo = n->edgesTo();

            const unsigned int size = edgesTo.count();
            for (unsigned int i = 0; i < size; i++)
            {
                edge = edgesTo.at(i);
                edge->setSelected(true);
                edge->update();
            }
        }
        return ContinueTraversing;
    }
};


class SelectAncestorsAction
{
public:
    VisitAction visitNode(GuiNode* n)
    {
        QList<Edge*> edgesFrom;
        QList<Edge*> edgesTo = n->edgesTo();

        const unsigned int size = edgesTo.count();

        for (unsigned int i = 0; i < size; i++)
        {
            Edge* edge = edgesTo.at(i);

            if (edge->isSelected())
            {
                n->setSelected(true);
                n->update();
            }

        }
        if (n->isSelected())
        {
            edgesFrom = n->edgesFrom();
            Edge* edge;
            if (!edgesFrom.isEmpty())
            {
                edge = edgesFrom.at(0);
                edge->setSelected(true);
                edge->update();
            }
        }
        return ContinueTraversing;
    }
};

class SelectCollectorAction
{
public:

    VisitAction visitNode(GuiNode* n)
    {
        Traverser<GuiNode, SelectAncestorsAction, AlwaysTruePredicate> tAncestor;
        SelectAncestorsAction aAncestor;
        tAncestor.traverseAncestors(n, aAncestor);

        return ContinueTraversing;
    }
};


GraphWidget::GraphWidget(Locations::LocationManager& locationManager, QWidget* parent)
    : QGraphicsView(parent),
      lm(locationManager)
{
    //Properties
    setCacheMode(CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);
    rotate(qreal(-90));
    setParent(parent);
}

GraphWidget::~GraphWidget()
{
    QGraphicsScene* scene;
    if (this->scene() != NULL)
    {
        scene = this->scene();
        QListIterator<QGraphicsItem*> items(scene->items());
        while (items.hasNext())
        {
            scene->removeItem(items.next());
        }
    }
}

void GraphWidget::wheelEvent(QWheelEvent* event)
{
    scaleView(pow((double)2, -event->delta() / 240.0));
}

void GraphWidget::drawBackground(QPainter* painter, const QRectF& rect)
{
    Q_UNUSED(rect);
    Q_UNUSED(painter);
}

void GraphWidget::scaleView(qreal scaleFactor)
{
    scale(scaleFactor, scaleFactor);
    this->scene()->update();
}

void GraphWidget::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
}

QPointF GraphWidget::drawTreeAux(QGraphicsScene* scene, GuiNode* node, float depth, unsigned int* leafNumber)
{
    ListIterator<GuiNode, Domain::Node>  it = node->getChildrenIterator<GuiNode>();
    list<QPointF> points;
    QPointF nodeCoord;
    QPointF ret;
    QPointF first;
    QPointF last;
    QGraphicsTextItem* text;
    Edge* edge;
    if (node->isLeaf())
    {
        nodeCoord.setX((*leafNumber) * 100);
        nodeCoord.setY((depth + node->getBranchLength()) * 100);
        ++(*leafNumber);
    }
    else
    {
        while (!it.end())
        {
            GuiNode* auxNode = it.get();
            ret = drawTreeAux(scene, auxNode, depth + node->getBranchLength(), leafNumber);
            points.push_front(ret);
            it.next();
        }
        last = points.front();
        first = points.back();
        nodeCoord.setX((first.x() + (last.x() - first.x()) / 2.0));
        nodeCoord.setY((depth + node->getBranchLength()) * 100);
    }

    node->setPos(nodeCoord.x() + 200, nodeCoord.y() + 200);

    if (node->isLeaf())
    {
        text = new QGraphicsTextItem(QString(node->getName().c_str()));
        text->setPos(nodeCoord.x() + 200 + 10, nodeCoord.y() + 200 + 20);
        text->rotate(90);
        node->setGraphicsName(text);
        scene->addItem(text);
    }

    it.restart();

    for (; !it.end(); it.next())
    {
        GuiNode* auxNode = it.get();
        edge = new Edge(node, auxNode);
        if (!node->isExpanded() || !node->isVisible())
        {
            edge->setVisible(false);
        }

        scene->addItem(edge);

        auxNode->addEdgeFrom(edge);
        node->addEdgeTo(edge);
    }
    scene->addItem(node);

    return nodeCoord;
}

void GraphWidget::drawTree(QGraphicsScene* scene, GuiNode* node)
{
    unsigned int leafNumber = 0;
    unsigned int depth = 50;

    drawTreeAux(scene, node, depth, &leafNumber);
}

void GraphWidget::draw(ITree<GuiNode>* tree)
{
    //Reset properties (only usefull when drawing more than one tree)
    resetCachedContent();
    resetMatrix();
    resetTransform();

    //Set Properties
    setCacheMode(CacheBackground);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);
    rotate(qreal(-90));


    //Create scene
    QGraphicsScene* scene;
    if (this->scene() != NULL)
    {
        scene = this->scene();
        QListIterator<QGraphicsItem*> items(scene->items());
        while (items.hasNext())
        {
            scene->removeItem(items.next());
        }
        delete scene;
    }
    scene = new QGraphicsScene(this);
    this->setScene(scene);
    this->tree = tree;
    drawTree(this->scene(), tree->getRoot());

    //Ensure visibility of the tree
    this->fitInView(this->scene()->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void GraphWidget::draw()
{
    if (tree != NULL)
        drawTree(this->scene(), tree->getRoot());
}

void GraphWidget::paintNode(QColor color, ITree<GuiNode>* tree)
{
    Traverser<GuiNode, ColorAction, IsSelectedPredicate> t;
    ColorAction v = ColorAction(color);

    GuiNode* const startNode = tree->getRoot();
    t.traverseDescendants(startNode, v);
}

void GraphWidget::selectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectAction, AlwaysTruePredicate> t;
    SelectAction a;

    GuiNode* const startNode = tree->getRoot();
    t.traverseDescendants(startNode, a);
}

void GraphWidget::unSelectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, UnSelectAction, AlwaysTruePredicate> t;
    UnSelectAction a;
    GuiNode* const startNode = tree->getRoot();
    t.traverseDescendants(startNode, a);
}

void GraphWidget::selectNodeDescendants(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectDescendantsAction, AlwaysTruePredicate> t;
    SelectDescendantsAction a;

    GuiNode* const startNode = tree->getRoot();
    t.traverseDescendants(startNode, a);
}

void GraphWidget::selectNodeAncestors(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectCollectorAction, IsSelectedPredicate> t;
    SelectCollectorAction a;

    GuiNode* const startNode = tree->getRoot();

    t.traverseDescendants(startNode, a);
}

void GraphWidget::clearNodeColoring(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, ClearColorAction, AlwaysTruePredicate> t;
    ClearColorAction a;

    GuiNode* const startNode = tree->getRoot();

    t.traverseDescendants(startNode, a);
}

QSize GraphWidget::sizeHint() const
{
    return QSize(600, 300);
}

Locations::LocationManager& GraphWidget::getLocationManager() const
{
    return lm;
}
