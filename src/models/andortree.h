#ifndef ANDORTREE_H
#define ANDORTREE_H

#include "node.h"
#include <QJsonObject>

// Polymorphic tree container
template <class T>
class AndOrTree
{
private:
    Node<T> *root;

public:
    AndOrTree(NodeType type)
    {
        root = new Node<T>(type);
    }
    Node<T> *addNode(Node<T> *parent, NodeType type)
    {
        Node<T> *newNode = new Node<T>(type);
        parent->addChild(newNode);
        return newNode;
    }
    Node<T> *addLeaf(Node<T> *parent, T *data)
    {
        Node<T> *newNode = new Node<T>(data);
        parent->addChild(newNode);
        return newNode;
    }
    // Returns root element
    Node<T> *getRoot()
    {
        return root;
    }
    // Tree destructor
    ~AndOrTree()
    {
        /// TODO Max implement
    }

    void read(const QJsonObject &json)
    {

        /// TODO Max implement http://doc.qt.io/qt-5/qtcore-json-savegame-example.html
    }

    void write(QJsonObject &json) const
    {
        json["root"] = "some root";
        /// TODO Max implement http://doc.qt.io/qt-5/qtcore-json-savegame-example.html
    }
};

#endif // ANDORTREE_H
