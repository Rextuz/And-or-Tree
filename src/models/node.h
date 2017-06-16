#ifndef NODE_H
#define NODE_H

#include <vector>
using std::vector;

#include <iostream>
using std::cout;
using std::endl;
namespace kkcs {
enum NodeType { t_and, t_or, t_leaf };

template <class T>
class Node {
public:
    class Iterator {
    private:
        Node<T> *parent;
        size_t index = 0;
    public:
        void setParent(Node<T> *parent) {
            this->parent = parent;
        }

        void setIndex(size_t index) {
            this->index = index;
        }

        Node getValue() {
            return parent->getChild(index);
        }

        Node<T> *getParent() const {
            return parent;
        }

        int getIndex() const {
            return index;
        }

        Iterator operator++( int ) {
            if (index < parent->getChildren()->size())
                index++;
            return *this;
        }

        inline bool operator==(const Iterator& rhs) {
            if (this->getParent() == rhs.getParent())
                if (this->getIndex() == rhs.getIndex())
                    return true;

            return false;
        }

        inline bool operator!=(const Iterator& rhs) {
            return !(*this == rhs);
        }
    };

    class Allocator {
    public:
        static const size_t chunk_size = sizeof(Node<T>);

    public:
        static Node<T> *allocate(size_t n) {
            return (Node<T>*) calloc(n, chunk_size);
        }
        static void deallocate(Node<T> *node, size_t n) {
            for (size_t i = 0; i < n; i++)
                free(node + i*chunk_size);
        }
        static void construct(Node<T> *node, NodeType type) {
            node->type = type;
        }
        static void construct(Node<T> *node, T* data) {
            node->type = t_leaf;
            node->data = data;
        }
        static void destroy(Node<T> *node) {
            if (node->type == t_leaf)
                delete node->data;
        }
    };

private:
    Node<T> *parent;
    vector<Node<T>*> *children = new vector<Node<T>*>();
    NodeType type;
    T *data;
    Iterator iterator;

public:
    Iterator getIterator() {
        return iterator;
    }

    Iterator begin() {
        Iterator begin_it = getChild(0)->getIterator();
        begin_it.setParent(this);
        begin_it.setIndex(0);
        return begin_it;
    }

    Iterator end() {
        size_t last = children->size() - 1;
        Iterator end_it = getChild(last)->getIterator();
        end_it.setParent(this);
        end_it.setIndex(last);
        return end_it;
    }

    size_t size() {
        size_t this_size = children->size();
        for (size_t i = 0; i < children->size(); i++) {
            this_size += children->at(i)->size();
        }
        return this_size;
    }

    // And/Or node
    Node(Node<T> *parent, NodeType type)
    {
        this->parent = parent;
        this->type = type;
        this->weight = 1;
    }

    // Leaf
    Node(Node<T> *parent, T *data)
    {
        this->parent = parent;
        this->type = t_leaf;
        this->data = data;
        //random weight
        this->weight = rand()%10;
    }

    // Destructor
    ~Node()
    {
        for (size_t i = 0; i < children->size(); i++)
            delete children->at(i);
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

    // Delete child by pointer
    void deleteChild(Node<T>* node)
    {
        for (size_t i = 0; i < children->size(); i++) {
            if (children->at(i) == node) {
                deleteChild(i);
                return;
            }
        }
    }

    // Delete self
    void deleteSelf()
    {
        parent->deleteChild(this);
    }

    T *getData()
    {
        if (type == t_leaf)
            return data;
        return nullptr;
    }

    int getWeight()
    {
        return weight;
    }

    NodeType getType()
    {
        return type;
    }

    void setType(NodeType type)
    {
        if (this->type != t_leaf)
            this->type = type;
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

    Node<T> *getParent()
    {
        return parent;
    }
};
}

#endif // NODE_H
