#include "src/ui/mainwindow.h"
#include <QApplication>

#include "../models/andortree.h"
#include "src/models/lexicalpair.h"
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
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_or);

    // Add nodes
    Node<LexicalPair> *node1 = tree->addNode(tree->getRoot(), t_and);
    Node<LexicalPair> *node2 = tree->addNode(tree->getRoot(), t_or);
    tree->addNode(node1, t_or);
    tree->addNode(node2, t_or);
    tree->addNode(node2, t_and);
    // End of Tree test

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
