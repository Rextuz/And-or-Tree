#include "src/ui/mainwindow.h"
#include <QApplication>

#include "src/models/andortree.h"
#include "src/models/joketemplate.h"
#include "src/logic/storage.h"
#include "src/logic/ctcreator.h"
#include "src/logic/joketemplatecreator.h"
#include "src/logic/tasktemplatecreator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    // Tree test
    // Create tree
    /*
    AndOrTree<int> *tree = new AndOrTree<int>(t_or);

    // Add nodes
    Node *node1 = tree->addNode(tree->getRoot(), t_and);
    Node *node2 = tree->addNode(tree->getRoot(), t_or);
    tree->addNode(node1, t_or);
    tree->addNode(node2, t_or);
    tree->addNode(node2, t_and);
    */
    // End of Tree test

    // LexicalTree test
    LexicalTree *ltree = new LexicalTree(t_or);
    Node *lnode1 = ltree->addNode(ltree->getRoot(), t_or);
    Node *lnode2 = ltree->addNode(ltree->getRoot(), t_or);
    Node *lnode3 = ltree->addNode(lnode2, t_or);
    ltree->addLeaf(lnode1, "A", "hello");
    ltree->addLeaf(lnode3, "B", "world");
    ltree->addLeaf(lnode3, "C", "mthrfckr");
    // End of LexicalTree test

    // Create storage of objects and load data from disk
    Storage& storage = Storage::Instance();
    storage.loadData();

    // Use Factory methods to create templates
    CTCreator* creator1 = new JokeTemplateCreator();
    CTCreator* creator2 = new TaskTemplateCreator();
    ContentTemplate* contentTemplate1 = creator1->createTemplate("I'm a joke");
    ContentTemplate* contentTemplate2 = creator2->createTemplate("I'm a task");
    storage.save(contentTemplate1);
    storage.save(contentTemplate2);

    // Print storage
    storage.printData();

    // Generate somethings
    Content* content1 = contentTemplate1->generateContent();
    std::cout << "content1 = " << content1->getStr() << "\n";
    Content* content2 = contentTemplate2->generateContent();
    std::cout << "content2 = " << content2->getStr() << "\n";

    return a.exec();
}
