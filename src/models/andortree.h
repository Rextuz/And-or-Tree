#ifndef ANDORTREE_H
#define ANDORTREE_H

#include <list>

enum NodeType { t_and, t_or };

// polymorphic tree container
class AndOrTree
{
public:
    class Node {
    private:
        std::list<Node*> children;
    public:
        Node();
        void addChild(Node *node);
        void *value;
    };

    class OrNode : public Node {
    public:
        OrNode();
    };

    class AndNode : public Node {
    public:
        AndNode();
    };

    Node *root;

    AndOrTree(NodeType type);
    Node *addNode(Node *parent, NodeType type);
    ~AndOrTree();
};

#endif // ANDORTREE_H
