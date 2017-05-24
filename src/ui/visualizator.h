#ifndef VISUALIZATOR_H
#define VISUALIZATOR_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItem>

#include "src/models/andortree.h"

class Visualizator
{
public:
    Visualizator(AndOrTree<LexicalPair> *tree);
    ~Visualizator() {}

    QGraphicsScene* getScene();
    QGraphicsView* getView();

private:
    void drawNode(Node<LexicalPair> *tree, int x, int y);

    AndOrTree<LexicalPair> *tree;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QFont font;
};

#endif // VISUALIZATOR_H
