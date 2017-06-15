#include <QtTest>
#include "test_andortree.h"
#include "src/models/andortree.h"
using kkcs::AndOrTree;

#include "src/models/lexicalpair.h"
using kkcs::LexicalPair;

#include "src/models/node.h"
using kkcs::Node;
using kkcs::t_leaf;
using kkcs::t_and;
using kkcs::t_or;

UTestTree::UTestTree(QObject *parent) : QObject(parent)
{

}

void UTestTree::createTree()
{
    AndOrTree<LexicalPair> tree(t_or);
    Node<LexicalPair> root = *tree.getRoot();
    //QCOMPARE(root.getParent(), nullptr);
    //QCOMPARE(root.getType(), t_or);
}

void UTestTree::addNode()
{
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);
    Node<LexicalPair> *root = tree->getRoot();
    Node<LexicalPair> *node = tree->addNode(tree->getRoot(), t_or);

    //QCOMPARE(node->getData(), nullptr);
    //QCOMPARE(node->getParent(), root);
    //QCOMPARE(node->getType(), t_or);

    //QCOMPARE(root->getChild(0), node);
}

void UTestTree::addLeaf()
{
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);
    Node<LexicalPair> *root = tree->getRoot();
    LexicalPair *data = new LexicalPair("key", "value");

    QCOMPARE(data->getKey(), (string)"key");
    QCOMPARE(data->getValue(), (string)"value");

    Node<LexicalPair> *leaf = tree->addLeaf(tree->getRoot(), data);

    //QCOMPARE(leaf->getData(), data);
    //QCOMPARE(leaf->getParent(), root);
    //QCOMPARE(leaf->getType(), t_leaf);

    //QCOMPARE(root->getChild(0), leaf);
}

void UTestTree::deleteNode()
{
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);
    Node<LexicalPair> *root = tree->getRoot();
    Node<LexicalPair> *node = tree->addNode(root, t_or);
    LexicalPair *data = new LexicalPair("key", "value");
    tree->addLeaf(node, data);

    root->deleteChild(0);

    //QCOMPARE(root->hasChildren(), false);
    //QCOMPARE(node->getData(), nullptr);
}

void UTestTree::treeSize()
{
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);

    //QCOMPARE((int)tree->size(), 1);

    tree->addNode(tree->getRoot(), t_or);

    //QCOMPARE((int)tree->size(), 2);

    Node<LexicalPair> *actions = tree->addNode(tree->getRoot(), t_and);
    tree->addNode(actions, t_and);
    tree->addNode(actions, t_or);

    //QCOMPARE((int)tree->size(), 5);
}
