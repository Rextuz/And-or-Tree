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

Node<LexicalPair> *deserialize(QDomDocument *document, QDomElement *_nodeEl, Node<LexicalPair> *parent)
{
    Node<LexicalPair> *current = nullptr;

    QDomElement nodeEl;
    if (_nodeEl == nullptr)
        nodeEl = document->documentElement();
    else
        nodeEl = *_nodeEl;

    QString typeAttr = nodeEl.attribute("type");
    if (typeAttr == "2"/*t_leaf*/)
    {
        QDomElement dataEl = nodeEl.firstChildElement("data");
        QString keyAttr = dataEl.attribute("key");
        QString valueAttr = dataEl.attribute("value");
        LexicalPair *data = new LexicalPair(keyAttr.toUtf8().constData(), valueAttr.toUtf8().constData());
        current = new Node<LexicalPair>(parent, data);
    } else if (typeAttr == "1")
        current = new Node<LexicalPair>(parent, t_or);
    else if (typeAttr == "0")
        current = new Node<LexicalPair>(parent, t_and);

    QDomElement children = nodeEl.firstChildElement("children");
    QDomNodeList nodes = children.childNodes();
    for (int i = 0; i < nodes.size(); i++)
    {
        QDomNode tmpNode = nodes.item(i);
        QDomElement currentNode = tmpNode.toElement();
        Node<LexicalPair> *newNode = deserialize(document, &currentNode, current);
        current->addChild(newNode);
    }
    return current;
}

AndOrTree<LexicalPair> *readTree(const QString filename) {
    QDomDocument *document = new QDomDocument();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly) || !document->setContent(&file))
        qDebug() << "Error while opening the file " << filename << endl;

    Node<LexicalPair> *root = deserialize(document);

    file.close();

    return new AndOrTree<LexicalPair>(root);
}


void writeTree(AndOrTree<LexicalPair> *tree, const QString filename)
{
    QDomDocument *document = new QDomDocument();

    serialize(tree->getRoot(), document);

    QFile file(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);

    stream << document->toString();

    file.close();
}
