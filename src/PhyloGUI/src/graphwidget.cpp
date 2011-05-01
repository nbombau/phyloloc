#include "PhyloGUI/inc/graphwidget.h"
#include "Phylopp/Traversal/INodeVisitor.h"
#include "Phylopp/Traversal/Traverser.h"

using namespace Traversal;
using namespace Domain;
using namespace std;

class ColorVisitor : public INodeVisitor< GuiNode>
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

class SelectDescendantsVisitor : public INodeVisitor< GuiNode>
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


class SelectAncestorsVisitor : public INodeVisitor< GuiNode>
{
public:
    void visit(GuiNode& n)
    {
    	/*QList<Edge *> edgesTo;
    	edgesTo=n.edgesTo();
    	Edge * edge=edgesTo.at(0);
        if(n.isSelected() || (edge!=NULL && edge->isSelected()))
        {
        	printf("ACA");
			unsigned int i=0;
			unsigned int size;
        	n.setSelected(true);
        	n.update();
        	QList<Edge *> edgesFrom = n.edgesFrom();
			size=edgesFrom.count();
			for(;i<size;i++)
        	{
				edge=edgesFrom.at(i);
				edge->setSelected(true);
				edge->update();
        	}
        }*/
    	printf("ACAACACACACA\n");
    	QList<Edge *> edgesTo;
    	QList<Edge *> edgesFrom;
    	edgesTo=n.edgesTo();
		unsigned int i=0;
		unsigned int size=edgesTo.count();
		Edge * edge;
		for(;i<size;i++)
		{
			printf("ACA1\n");
			edge=edgesTo.at(i);
			if(edge->isSelected())
			{
				printf("ACA2\n");
				n.setSelected(true);
				n.update();
			}

		}
		printf("ACA5\n");
		std::cout << n.isSelected() << "\n";
		std::cout << n.getName() << "\n";
		if(n.isSelected())
		{
			printf("ACA3\n");
			edgesFrom=n.edgesFrom();
			Edge * edge=edgesFrom.at(0);
			if(edge!=NULL)
			{
				printf("ACA4\n");
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
    QGraphicsScene* scene = new QGraphicsScene(this);
    //scene->setItemIndexMethod(QGraphicsScene::NoIndex);
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
    Traverser<GuiNode, ColorVisitor> t = Traverser<GuiNode, ColorVisitor>();
    ColorVisitor v = ColorVisitor(color);
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectVisitor> t = Traverser<GuiNode, SelectVisitor>();
    SelectVisitor v = SelectVisitor();
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::unSelectAllNodes(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, UnSelectVisitor> t = Traverser<GuiNode, UnSelectVisitor>();
    UnSelectVisitor v = UnSelectVisitor();
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectNodeDescendants(ITree<GuiNode>* tree)
{
    Traverser<GuiNode, SelectDescendantsVisitor> t = Traverser<GuiNode, SelectDescendantsVisitor>();
    SelectDescendantsVisitor v = SelectDescendantsVisitor();
    GuiNode& startNode = *tree->getRoot();
    t.traverseDown(startNode, v);
}

void GraphWidget::selectNodeAncestors(ITree<GuiNode>* tree)
{
	printf("Llegue al ancestors");
	Traverser<GuiNode, SelectAncestorsVisitor> t = Traverser<GuiNode, SelectAncestorsVisitor>();
	SelectAncestorsVisitor v = SelectAncestorsVisitor();
	GuiNode& startNode = *tree->getRoot();
	t.traverseUp(startNode, v);
}

