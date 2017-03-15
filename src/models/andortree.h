#ifndef ANDORTREE_H
#define ANDORTREE_H

#include "node.h"

// polymorphic tree container
class AndOrTree
{
private:
    Node *root;

public:
    AndOrTree(NodeType type);
    Node *addNode(Node *parent, NodeType type);
    Node *addLeaf(Node *parent, void *data);
    Node *getRoot();
    ~AndOrTree();
};

#endif // ANDORTREE_H
