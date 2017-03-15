#ifndef NODE_H
#define NODE_H

#include <list>

using std::list;

enum NodeType { t_and, t_or, t_leaf };

// Node
class Node {
private:
    list<Node*> children;
    NodeType type;
    void *data;
public:
    Node(NodeType type);
    Node(void *data);
    void addChild(Node *node);
    void *getData();
    NodeType getType();
};

#endif // NODE_H
