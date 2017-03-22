#ifndef LEXICALTREE_H
#define LEXICALTREE_H

#include "andortree.h"

#include <string>
using std::string;

class LexicalPair
{
private:
    string key;
    string value;

public:
    LexicalPair(string key, string value)
    {
        this->key.assign(key);
        this->value.assign(value);
    }

    string getKey()
    {
        return key;
    }

    string getValue()
    {
        return value;
    }
};

// tree with data like "A"="xyz"
class LexicalTree : public AndOrTree
{
public:
    LexicalTree(NodeType type);
    Node *addLeaf(Node *parent, string key, string value);
};

#endif // LEXICALTREE_H
