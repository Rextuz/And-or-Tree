#ifndef ANDORTREE_H
#define ANDORTREE_H

#include "node.h"

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

    }
};

#endif // ANDORTREE_H
