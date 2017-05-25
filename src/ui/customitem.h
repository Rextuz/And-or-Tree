#ifndef CUSTOMITEM_H
#define CUSTOMITEM_H

#include <QDebug>
#include <QGraphicsRectItem>

#include "src/models/andortree.h"
#include "src/models/lexicalpair.h"
#include "templatemenu.h"

class CustomItem : public QGraphicsRectItem
{
public:
    CustomItem(Node<LexicalPair> *tree)
    {
        this->tree = tree;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        TemplateMenu::handleCustomItem();
        qDebug() << "Custom item clicked.";
    }

private:
    Node<LexicalPair> *tree;
};

#endif // CUSTOMITEM_H
