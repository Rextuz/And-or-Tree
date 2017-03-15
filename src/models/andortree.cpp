#include "andortree.h"

/*
 * Tree constructor
 *      type = type for the root node
 */
AndOrTree::AndOrTree(NodeType type)
{
    root = new Node(type);
}

Node *AndOrTree::addNode(Node *parent, NodeType type)
{
    Node *newNode = new Node(type);
    parent->addChild(newNode);
    return newNode;
}

Node *AndOrTree::addLeaf(Node *parent, void *data)
{
    Node *newNode = new Node(data);
    parent->addChild(newNode);
    return newNode;
}

// Returns root element
Node *AndOrTree::getRoot()
{
    return root;
}

// Tree destructor
AndOrTree::~AndOrTree()
{

}
