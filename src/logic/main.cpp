#include "src/ui/mainwindow.h"
#include <QApplication>

#include "src/models/andortree.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Tree test
    AndOrTree *tree = new AndOrTree(t_or);
    AndOrTree::Node *node1 = tree->addNode(tree->root, t_and);
    AndOrTree::Node *node2 = tree->addNode(tree->root, t_or);
    tree->addNode(node1, t_or);
    tree->addNode(node2, t_or);
    tree->addNode(node2, t_and);
    // End of Tree test

    return a.exec();
}
