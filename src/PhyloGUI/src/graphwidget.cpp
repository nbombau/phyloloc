#include "PhyloGUI/inc/graphwidget.h"
#include "Phylopp/Traversal/INodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

using namespace Traversal;
using namespace Domain;
using namespace std;

class ColorVisitor
{
public:
    ColorVisitor(QColor c)
    {
        color = c;
    }

    void visit(GuiNode& n)
    {
        if (n.isSelected())
        {
            n.setColor(color);
            n.setSelected(false);
            n.update();
        }
    }

private:
    QColor color;
};


class SelectVisitor
{
public:
    void visit(GuiNode& n)
    {
        n.setSelected(true);
        n.update();
    }
};

class SelectCollectorVisitor
{
public:
	queue<GuiNode*, list< GuiNode*> > getNodes()
	{
		return nodes;
	}

    void visit(GuiNode& n)
    {
        if(n.isSelected())
        {
        	nodes.push(&n);
        }
    }
private:
    queue<GuiNode*, list< GuiNode*> > nodes;
};

class UnSelectVisitor
{
public:
    void visit(GuiNode& n)
    {
    	unsigned int i=0;
		unsigned int size;
        n.setSelected(false);
        n.update();
        Edge * edge;
        QList<Edge *> edgesTo = n.edgesTo();
		size=edgesTo.count();
		for(;i<size;i++)
		{
			edge=edgesTo.at(i);
			edge->setSelected(false);
			edge->update();
		}
    }
};

class SelectDescendantsVisitor
{
public:
    void visit(GuiNode& n)
    {
    	QList<Edge *> edgesFrom;
    	edgesFrom=n.edgesFrom();
    	Edge * edge=edgesFrom.at(0);
        if(n.isSelected() || (edge!=NULL && edge->isSelected()))
        {
			unsigned int i=0;
			unsigned int size;
        	n.setSelected(true);
        	n.update();
        	QList<Edge *> edgesTo = n.edgesTo();
			size=edgesTo.count();
			for(;i<size;i++)
        	{
				edge=edgesTo.at(i);
				edge->setSelected(true);
				edge->update();
        	}
        }
    }
};


class SelectAncestorsVisitor
{
public:
    void visit(GuiNode& n)
    {
    	QList<Edge *> edgesTo;
    	QList<Edge *> edgesFrom;
    	edgesTo=n.edgesTo();
		unsigned int i=0;
		unsigned int size=edgesTo.count();
		Edge * edge;
		for(;i<size;i++)
		{
			edge=edgesTo.at(i);
			if(edge->isSelected())
			{
				n.setSelected(true);
				n.update();
			}

		}
		if(n.isSelected())
		{
			edgesFrom=n.edgesFrom();
			Edge * edge=edgesFrom.at(0);
			if(edge!=NULL)
			{
				edge->setSelected(true);
				edge->update();
			}
		}

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
    rotate(qreal(-90));
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
    Edge* edge;
    if (node->isLeaf() || !node->isExpanded())
    {
        nodeCoord.setX((*leafNumber) * 100);
        nodeCoord.setY((depth + node->getBranchLength()) * 100);
        ++(*leafNumber);
        //QGraphicsTextItem text* =scene->addText("hola");
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

    node->setPos(nodeCoord.x() + 200, nodeCoord.y() + 200);
    scene->addItem(node);

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
    QGraphicsScene* scene = new QGraphicsScene(this);
    this->setScene(scene);

    drawTree(scene, tree->getRoot());

    this->adjustSize();
}


void GraphWidget::resizeEvent(QResizeEvent*)
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

void GraphWidget::paintNode(QColor color, ITree<GuiNode>* tree)
{
    Traverser<GuiNode, ColorVisitor> t;
    ColorVisitor v = ColorVisitor(color);
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectVisitor> t;
    SelectVisitor v;
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::unSelectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, UnSelectVisitor> t;
    UnSelectVisitor v;
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectNodeDescendants(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectDescendantsVisitor> t;
    SelectDescendantsVisitor v;
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectNodeAncestors(ITree<GuiNode>* tree)
{
	Traverser<GuiNode, SelectCollectorVisitor> t;
	SelectCollectorVisitor v;
	GuiNode& startNode = *tree->getRoot();
	t.traverseDown(startNode, v);
	queue<GuiNode*, list< GuiNode*> > nodes =v.getNodes();
	std::cout << nodes.size();

	Traverser<GuiNode, SelectAncestorsVisitor> tAncestor;
	SelectAncestorsVisitor vAnvestor;
	while(!nodes.empty())
	{
		GuiNode & startNode = *nodes.front();
		tAncestor.traverseUp(startNode, vAnvestor);
		nodes.pop();
	}
}

