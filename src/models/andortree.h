#ifndef ANDORTREE_H
#define ANDORTREE_H

#include "node.h"

// Polymorphic tree container
template <class T>
class AndOrTree
{
private:
    Node *root;
    T *value;

public:
    AndOrTree(NodeType type);
    virtual Node *addNode(Node *parent, NodeType type);
    virtual Node *addLeaf(Node *parent, T *data);
    virtual Node *getRoot();
    ~AndOrTree();
};

#endif // ANDORTREE_H
