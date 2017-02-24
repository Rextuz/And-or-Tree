#include "andortree.h"

// Tree constructor
AndOrTree::AndOrTree(NodeType type)
{
    if (type == t_or)
        root = new OrNode();
    else
        root = new AndNode();
}

AndOrTree::Node *AndOrTree::addNode(Node *parent, NodeType type)
{
    Node *newNode;
    if (type == t_or)
        newNode = new OrNode();
    else if (type == t_and)
        newNode = new AndNode();
    parent->addChild(newNode);
    return newNode;
}

// Tree destructor
AndOrTree::~AndOrTree()
{

}

// Tree node
AndOrTree::Node::Node()
{

}

// Add child to a node
void AndOrTree::Node::addChild(Node *node) {
    children.push_back(node);
}

// Or Node
AndOrTree::OrNode::OrNode()
{

}

// And node
AndOrTree::AndNode::AndNode()
{

}
