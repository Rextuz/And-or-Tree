#ifndef LEXICALTREE_H
#define LEXICALTREE_H

#include "andortree.h"

// tree with data like "A"="xyz"
class LexicalTree : public AndOrTree
{
public:
    LexicalTree(NodeType type);
};

#endif // LEXICALTREE_H
