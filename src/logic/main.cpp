#include "src/ui/mainwindow.h"
#include <QApplication>

#include "src/models/andortree.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Tree test
    // Create tree
    AndOrTree *tree = new AndOrTree(t_or);

    // Add nodes
    Node *node1 = tree->addNode(tree->getRoot(), t_and);
    Node *node2 = tree->addNode(tree->getRoot(), t_or);
    tree->addNode(node1, t_or);
    tree->addNode(node2, t_or);
    Node *node3 = tree->addNode(node2, t_and);

    // Add leaf
    int val = 42;
    int *valp = &val;
    tree->addLeaf(node3, valp);
    // End of Tree test

    return a.exec();
}
