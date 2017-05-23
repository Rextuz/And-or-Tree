#ifndef LEXICALPAIR_H
#define LEXICALPAIR_H

#include "andortree.h"

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <map>
using std::map;
using std::make_pair;

class LexicalPair
{
private:
    string key;
    string value;

    static void generateDictionary(Node<LexicalPair> *tree, unsigned int seed, map<string, string> *dictionary)
    {
        // Choose your path
        switch (tree->getType()) {
        case t_or:      // We'll have to go one way
        {
            if (tree->hasChildren())
            {
                srand(seed);    // randomize stuff
                int path = rand() % tree->getChildren()->size();
                generateDictionary(tree->getChild(path), seed, dictionary);
            }
            break;
        }
        case t_and:     // We will check out each path
        {
            for (unsigned int i = 0; i < tree->getChildren()->size(); i++)
                generateDictionary(tree->getChild(i), seed, dictionary);

            break;
        }
        case t_leaf:    // Collect this
        {
            string key = tree->getData()->getKey();
            string value = tree->getData()->getValue();
            dictionary->insert(make_pair(key, value));
            break;
        }
        default:        // Unreachable
            break;
        }
    }

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

    static map<string, string> getDictionary(Node<LexicalPair> *tree, unsigned int seed) {
        map<string, string> dictionary;

        generateDictionary(tree, seed, &dictionary);
        return dictionary;
    }
};

#endif // LEXICALPAIR_H
