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
    CustomItem(Node<LexicalPair> *tree, TemplateMenu *templateMenu)
    {
        this->tree = tree;
        this->templateMenu = templateMenu;
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
        templateMenu->handleCustomItem(tree);
        QGraphicsItem::mousePressEvent(event);
    }

private:
    Node<LexicalPair> *tree;
    TemplateMenu *templateMenu;
};

#endif // CUSTOMITEM_H
