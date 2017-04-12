#ifndef LEXICALPAIR_H
#define LEXICALPAIR_H

#include <string>
#include <vector>
#include "andortree.h"

using std::string;
using std::vector;

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

    static void getDictionary(Node<LexicalPair> *tree, unsigned int seed, vector<LexicalPair*> *dictionary)
    {
        // Choose your path
        switch (tree->getType()) {
        case t_or:      // We'll have to go one way
        {
            if (tree->hasChildren())
            {
                srand(seed);    // randomize stuff
                int path = rand() % tree->getChildren()->size();
                getDictionary(tree->getChild(path), seed, dictionary);
            }
            break;
        }
        case t_and:     // We will check out each path
        {
            for (unsigned int i = 0; i < tree->getChildren()->size(); i++)
                getDictionary(tree->getChild(i), seed, dictionary);

            break;
        }
        case t_leaf:    // Collect this
        {
            dictionary->push_back(tree->getData());
            break;
        }
        default:        // Unreachable
            break;
        }
    }
};

#endif // LEXICALPAIR_H
