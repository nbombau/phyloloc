#include "PhyloGUI/inc/graphwidget.h"
#include "Phylopp/Traversal/INodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

/*#include "../../Domain/INode.h"
#include "../GuiAspect.h"
using namespace Domain;
typedef GuiAspect< Domain::BaseAspect> GuiNode;*/

using namespace Traversal;
using namespace Domain;
using namespace std;

class ColorVisitor : public INodeVisitor< GuiNode>
{
public:
    ColorVisitor(QColor c)
    {
        color=c;
    }

    void visit(GuiNode& n)
    {
        if(n.isSelected())
        {
            n.setColor(color);
            n.setSelected(false);
            n.update();
        }
    }

private:
    QColor color;
};


class SelectVisitor : public INodeVisitor< GuiNode>
{
public:
    void visit(GuiNode& n)
    {
        n.setSelected(true);
        n.update();
    }
};

class UnSelectVisitor : public INodeVisitor< GuiNode>
{
public:
    void visit(GuiNode& n)
    {
        n.setSelected(false);
        n.update();
    }
};

GraphWidget::GraphWidget(QWidget* parent)
    : QGraphicsView(parent)
{
    //Properties
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setDragMode(QGraphicsView::ScrollHandDrag);
    resize(parentWidget()->width(), parentWidget()->height());
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
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}



QPointF GraphWidget::drawTreeAux(QGraphicsScene* scene, GuiNode* node, float depth, unsigned int* leafNumber)
{
    ListIterator<GuiNode> * it = node->getChildrenIterator();
    list<QPointF> points;
    QPointF nodeCoord;
    QPointF ret;
    QPointF first;
    QPointF last;
    Edge * edge;
    if (node->isLeaf() || !node->isExpanded())
    {
        nodeCoord.setX((*leafNumber) * 100);
        nodeCoord.setY((depth + node->getBranchLength()) * 100);
        ++(*leafNumber);
    }
    else
    {
        while (!it->end())
        {
            GuiNode* auxNode = &it->get();
            ret = drawTreeAux(scene, auxNode, depth + node->getBranchLength(), leafNumber);
            points.push_front(ret);
            it->next();
        }
        last = points.front();
        first = points.back();
        nodeCoord.setX((first.x() + (last.x() - first.x()) / 2.0));
        nodeCoord.setY((depth + node->getBranchLength()) * 100);
    }

    node->setPos(nodeCoord.x()+200, nodeCoord.y()+200);
    scene->addItem(node);

    std::cout << node->getName() << "\n";

    it->restart();
    while (!it->end())
    {
        GuiNode* auxNode = &it->get();
        edge = new Edge(node, auxNode);

        scene->addItem(edge);
        auxNode->addEdgeFrom(edge);
        node->addEdgeTo(edge);
        it->next();
    }
    delete it;
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
    QGraphicsScene *scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    this->setScene(scene);
    /******************************************/

    drawTree(scene, tree->getRoot());

    this->adjustSize();
}


void GraphWidget::resizeEvent(QResizeEvent* event)
{
    resize(parentWidget()->width(), parentWidget()->height());
}

void GraphWidget::reScaleScene()
{
    const double sceneWidth = scene()->width();
    const double sceneHeight = scene()->height();
    const double parentWidth = parentWidget()->width();
    const double parentHeight = parentWidget()->height();
    printf("sceneWidth=%f sceneHeight=%f parentWidth=%f parentHeight=%f\n", sceneWidth, sceneHeight, parentWidth, parentHeight);

    if (sceneWidth > parentWidth)
    {
        printf("1\n");
        scale(qreal(parentWidth / sceneWidth), qreal(parentWidth / sceneWidth));
    }
    else if (sceneHeight > parentHeight)
    {
        printf("2\n");
        scale(qreal(parentHeight / sceneHeight), qreal(parentHeight / sceneHeight));
    }
    else if (sceneWidth < parentWidth)
    {
        printf("3\n");
        scale(qreal(parentWidth / sceneWidth), qreal(parentWidth / sceneWidth));
    }
    else
    {
        printf("4\n");
        scale(qreal(parentHeight / sceneHeight), qreal(parentHeight / sceneHeight));
    }
}


void traverseDown(GuiNode& t, ColorVisitor& v)
{
    //A queue shall be used to avoid recursion
    queue<GuiNode*, list<GuiNode*> > queue;

    //Push the root
    queue.push(&t);

    while (!queue.empty())
    {
        GuiNode & n = *queue.front();
        GuiNode * node = &n;
        queue.pop();

        //Visit the node that is on top of the queue
        v.visit(n);

        Domain::ListIterator<GuiNode>* it = (*node).getChildrenIterator();

        //And add the node's children to the queue
        while(!it->end())
        {
            node = &it->get();
            queue.push(node);
            it->next();
        }

        delete it;
    }
}

void traverseDown(GuiNode& t, UnSelectVisitor& v)
{
    //A queue shall be used to avoid recursion
    queue<GuiNode*, list<GuiNode*> > queue;

    //Push the root
    queue.push(&t);

    while (!queue.empty())
    {
        GuiNode & n = *queue.front();
        GuiNode * node = &n;
        queue.pop();

        //Visit the node that is on top of the queue
        v.visit(n);

        Domain::ListIterator<GuiNode>* it = (*node).getChildrenIterator();

        //And add the node's children to the queue
        while(!it->end())
        {
            node = &it->get();
            queue.push(node);
            it->next();
        }

        delete it;
    }
}

void traverseDown(GuiNode& t, SelectVisitor& v)
{
    //A queue shall be used to avoid recursion
    queue<GuiNode*, list<GuiNode*> > queue;

    //Push the root
    queue.push(&t);

    while (!queue.empty())
    {
        GuiNode & n = *queue.front();
        GuiNode * node = &n;
        queue.pop();

        //Visit the node that is on top of the queue
        v.visit(n);

        Domain::ListIterator<GuiNode>* it = (*node).getChildrenIterator();

        //And add the node's children to the queue
        while(!it->end())
        {
            node = &it->get();
            queue.push(node);
            it->next();
        }

        delete it;
    }
}


void GraphWidget::paintNode(QColor color,ITree<GuiNode>* tree)
{
    Traverser<GuiNode, ColorVisitor> t = Traverser<GuiNode, ColorVisitor>();
    ColorVisitor v = ColorVisitor(color);
    GuiNode & startNode = *tree->getRoot();
    traverseDown(startNode, v);
}

void GraphWidget::selectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectVisitor> t = Traverser<GuiNode, SelectVisitor>();
    SelectVisitor v = SelectVisitor();
    GuiNode & startNode = *tree->getRoot();
    traverseDown(startNode, v);
}

void GraphWidget::unSelectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, UnSelectVisitor> t = Traverser<GuiNode, UnSelectVisitor>();
    UnSelectVisitor v = UnSelectVisitor();
    GuiNode & startNode = *tree->getRoot();
    traverseDown(startNode, v);
}

void GraphWidget::selectNodeDescendants(ITree<GuiNode>* tree)
{
    printf("Seleccionar descendientes");
}

void GraphWidget::selectNodeAncestors(ITree<GuiNode>* tree)
{
    printf("Seleccionar descendientes");
}

