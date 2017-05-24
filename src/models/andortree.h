#ifndef ANDORTREE_H
#define ANDORTREE_H

#include <QJsonObject>

#include "node.h"
#include "serializer.h"

// Polymorphic tree container
template <class T>
class AndOrTree
{
private:
    Node<T> *root;
    AndOrTree(AndOrTree const&);
    AndOrTree& operator= (AndOrTree const&);

public:
    AndOrTree(NodeType type)
    {
        root = new Node<T>(type);
    }
    AndOrTree(Node<T> *root)
    {
        this->root = root;
    }

    size_t size() {
        return root->size() + 1;
    }

    Node<T> *addNode(Node<T> *parent, NodeType type)
    {
        Node<T> *newNode = new Node<T>(type);
        parent->addChild(newNode);
        return newNode;
    }
    Node<T> *addLeaf(Node<T> *parent, T *data)
    {
        Node<T> *newNode = new Node<T>(data);
        parent->addChild(newNode);
        return newNode;
    }

    typename Node<T>::Iterator begin() {
        return root->begin();
    }

    typename Node<T>::Iterator end() {
        return root->end();
    }

    // Returns root element
    Node<T> *getRoot()
    {
        return root;
    }
    // Tree destructor
    ~AndOrTree()
    {
        cout << "Tree destructor" << endl;
        delete root;
    }

    void write(const QString filename)
    {
        QDomDocument *document = new QDomDocument();

        serialize(this->getRoot(), document);

        QFile file(filename);
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream stream(&file);

        stream << document->toString();

        file.close();
    }
};

#endif // ANDORTREE_H
