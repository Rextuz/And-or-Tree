#include "visualizator.h"

QGraphicsScene* Visualizator::getScene()
{
    return scene;
}

QGraphicsView* Visualizator::getView()
{
    return view;
}

Visualizator::Visualizator(AndOrTree<LexicalPair> *tree)
{
    scene = new QGraphicsScene;
    view = new QGraphicsView;
    font.setFamily("Segoe UI Light");
    font.setPointSize(16);
    this->tree = tree;
    this->drawNode(tree->getRoot(),0,0);
}

void Visualizator::drawNode(Node<LexicalPair> *tree, int x, int y)
{
    if(tree->getType() == t_leaf)
    {
        QString str = QString::fromStdString("(" + tree->getData()->getKey()+ ")" + " " + tree->getData()->getValue());
        if(str.length() > 20)
        {
            str.truncate(20);
            str.append("...");
        }
        QGraphicsTextItem *leafItem = scene->addText(str,font);
        leafItem->setPos(x+5,y+5);
        scene->addRect(x,y,200,50);
    }
    else
    {
        if(tree->getType() == t_and)
        {
            QGraphicsTextItem *item = scene->addText("and",font);
            item->setPos(x+5,y+5);
        }
        else
        {
            QGraphicsTextItem *item = scene->addText("or",font);
            item->setPos(x+10,y+5);
        }
        scene->addEllipse(x,y,50,50);

        int size = tree->size();

        QGraphicsTextItem *plus = scene->addText("+",font);
        plus->setPos(x+15,y+5+70*size);
        scene->addEllipse(x,y+70*size,50,50);
        scene->addLine(x+25,y+50,x+25,y+70*size);

        if(tree->hasChildren())
        {
            scene->addLine(x+50,y+25,x+70,y+25);
        }

        size = 0;
        for (unsigned int i = 0; i < tree->getChildren()->size(); i++)
        {
            if(i == 0)
            {
                this->drawNode(tree->getChild(i),x+70,y);
            }
            else
            {
                scene->addLine(x+25,y+25+70*(size+i),x+70,y+25+70*(size+i));
                this->drawNode(tree->getChild(i),x+70,y+70*(size+i));
            }
            size += tree->getChild(i)->size();
        }
    }

    view->setScene(scene);
}
