#include "andortree.h"

/*
 * Tree constructor
 *      type = type for the root node
 */
template <class T>
AndOrTree<T>::AndOrTree(NodeType type)
{
    root = new Node(type);
}

template <class T>
Node *AndOrTree<T>::addNode(Node *parent, NodeType type)
{
    Node *newNode = new Node(type);
    parent->addChild(newNode);
    return newNode;
}

template <class T>
Node *AndOrTree<T>::addLeaf(Node *parent, T *data)
{
    Node *newNode = new Node(data);
    parent->addChild(newNode);
    return newNode;
}

// Returns root element
template <class T>
Node *AndOrTree<T>::getRoot()
{
    return root;
}

// Tree destructor
template <class T>
AndOrTree<T>::~AndOrTree()
{

}
