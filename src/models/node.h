#ifndef NODE_H
#define NODE_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;

enum NodeType { t_and, t_or, t_leaf };

template <class T>
class Node {
private:
    vector<Node<T>*> *children = new vector<Node<T>*>();
    NodeType type;
    T *data;

public:
    // And/Or node
    Node(NodeType type)
    {
        this->type = type;
    }
    ~Node()
    {
        cout << "Node destructor" << endl;
        for (size_t i = 0; i < children->size(); i++)
            delete children->at(i);
    }

    // Leaf
    Node(T *data)
    {
        this->type = t_leaf;
        this->data = data;
    }

    // Add child to a node
    void addChild(Node *node)
    {
        children->push_back(node);
    }

    // Delete child by index
    void deleteChild(int index)
    {
        Node<T>* node = children->at(index);
        children->erase(children->begin() + index);
        delete node;
    }

    T *getData()
    {
        if (type == t_leaf)
            return data;
        return nullptr;
    }
    NodeType getType()
    {
        return type;
    }
    bool hasChildren()
    {
        return !children->empty();
    }
    vector<Node<T>*> *getChildren()
    {
        return children;
    }
    Node<T> *getChild(int index)
    {
        return children->at(index);
    }
};

#endif // NODE_H
