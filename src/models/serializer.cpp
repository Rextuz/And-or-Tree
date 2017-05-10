#include "serializer.h"

void serialize(Node<LexicalPair> *node, QDomDocument *document, QDomElement *root)
{
    LexicalPair *data = node->getData();

    QDomElement nodeEl = document->createElement("node");
    nodeEl.setAttribute("type", node->getType());
    if (root == nullptr)
        document->appendChild(nodeEl);
    else
        root->appendChild(nodeEl);

    if (node->getType() == t_leaf)
    {
        QDomElement dataEl = document->createElement("data");
        dataEl.setAttribute("key", QString::fromStdString(data->getKey()));
        dataEl.setAttribute("value", QString::fromStdString(data->getValue()));
        nodeEl.appendChild(dataEl);
    }
    if (node->hasChildren())
    {
        QDomElement childrenEl = document->createElement("children");
        for (unsigned int i = 0; i < node->getChildren()->size(); i++)
            serialize(node->getChild(i), document, &childrenEl);
        nodeEl.appendChild(childrenEl);
    }
}

/*Node<LexicalPair> *deserialize()
{

}*/
