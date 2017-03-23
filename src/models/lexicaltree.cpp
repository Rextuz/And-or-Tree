#include "lexicaltree.h"

// Here ??????????????
LexicalTree::LexicalTree(NodeType type) : AndOrTree(type)
{

}

Node *LexicalTree::addLeaf(Node *parent, string key, string value)
{
    LexicalPair *pair = new LexicalPair(key, value);
    return AndOrTree::addLeaf(parent, pair);
}
