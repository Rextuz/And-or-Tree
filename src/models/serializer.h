#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>
using std::ostream;

#include "node.h"
#include "lexicalpair.h"

#define TAB for (int i = 0; i < level; i++) out << '\t';

void serialize(ostream &out, Node<LexicalPair> *node, int level)
{
    LexicalPair *data = node->getData();
    // string type;

    /*if (node->getType() == t_and)
        type = "and";
    else if (node->getType() == t_or)
        type = "or";
    else
        type = "leaf";*/

    if (level == 0)
        out << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << endl;

    TAB out << "<node>" << endl;
    TAB out << "<type>" << node->getType() << "</type>" << endl;
    if (node->getType() == t_leaf)
    {
        TAB out << "\t<data>" << endl;
        TAB out << "\t\t<key>" << data->getKey() << "</key>" << endl;
        TAB out << "\t\t<value>" << data->getValue() << "</value>" << endl;
        TAB out << "\t</data>" << endl;
    }
    if (node->hasChildren())
    {
        TAB out << "\t<children>" << endl;
        for (unsigned int i = 0; i < node->getChildren()->size(); i++)
            serialize(out, node->getChild(i), level + 1);
        TAB out << "\t</children>" << endl;
    }
    TAB out << "</node>" << endl;
}

#endif // SERIALIZER_H
