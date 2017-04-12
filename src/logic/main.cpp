#include "src/ui/mainwindow.h"
#include <QApplication>
#include <time.h>   // for random

#include <iostream> // for output
using std::cout;
using std::endl;

#include "../models/andortree.h"
#include "src/models/lexicalpair.h"
#include "src/models/joketemplate.h"
#include "src/logic/storage.h"
#include "src/logic/ctcreator.h"
#include "src/logic/joketemplatecreator.h"
#include "src/logic/tasktemplatecreator.h"

int main(int argc, char *argv[])
{
    // Tree test
    // Create tree
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);

    Node<LexicalPair> *characters = tree->addNode(tree->getRoot(), t_or);
    Node<LexicalPair> *actions = tree->addNode(tree->getRoot(), t_and);
    Node<LexicalPair> *actions_what = tree->addNode(actions, t_and);
    Node<LexicalPair> *actions_where = tree->addNode(actions, t_or);

    // Populate with characters
    tree->addLeaf(characters, new LexicalPair("A", "Max"));
    tree->addLeaf(characters, new LexicalPair("A", "Denis"));
    tree->addLeaf(characters, new LexicalPair("A", "Efim"));

    // Populate with actions
    tree->addLeaf(actions_what, new LexicalPair("B", "Dance"));
    tree->addLeaf(actions_what, new LexicalPair("B", "Sing"));
    tree->addLeaf(actions_where, new LexicalPair("C", "At home"));
    tree->addLeaf(actions_where, new LexicalPair("C", "In the forest"));

    // getDictionary() test
    cout << "\n-----Dictionary-----" << endl;
    vector<LexicalPair*> *dictionary = new vector<LexicalPair*>();
    LexicalPair::getDictionary(tree->getRoot(), time(nullptr), dictionary);
    for (unsigned int i = 0; i < dictionary->size(); i++)
    {
        LexicalPair *pair = dictionary->at(i);
        cout << pair->getKey() << ": " << pair->getValue() << endl;
    }
    cout << "-----End of Dictionary-----\n" << endl;
    // End of getDictionary() test
    // End of Tree test

    // Create storage of objects and load data from disk
    Storage& storage = Storage::Instance();
    storage.loadList();

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

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
