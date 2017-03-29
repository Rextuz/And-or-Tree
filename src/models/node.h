#ifndef NODE_H
#define NODE_H

#include <list>

using std::list;

enum NodeType { t_and, t_or, t_leaf };

template <class T>
class Node {
private:
    list<Node<T>*> children;
    NodeType type;
    T *data;

public:
    // And/Or node
    Node(NodeType type)
    {
        this->type = type;
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
        children.push_back(node);
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
};

#endif // NODE_H
