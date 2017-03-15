#include "node.h"

// And/Or node
Node::Node(NodeType type)
{
    this->type = type;
}

// Leaf
Node::Node(void *data)
{
    this->type = t_leaf;
    this->data = data;
}

// Add child to a node
void Node::addChild(Node *node) {
    children.push_back(node);
}

// Get data if leaf
void *Node::getData()
{
    if (type == t_leaf)
        return data;
    return nullptr;
}

// Get node type
NodeType Node::getType()
{
    return type;
}
