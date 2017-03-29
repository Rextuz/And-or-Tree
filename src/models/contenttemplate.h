#ifndef CONTENTTEMPLATE_H
#define CONTENTTEMPLATE_H

#include "content.h"
#include "andortree.h"
#include "lexicalpair.h"
#include <string>

// contains a template of text and a tree
class ContentTemplate
{
public:
    ContentTemplate(std::string title);
    ContentTemplate(std::string title, std::string text, AndOrTree<LexicalPair>* tree);

    virtual Content* generateContent() = 0;

    std::string getTitle() const;
    std::string getText() const;
    AndOrTree<LexicalPair> *getTree() const;
    int getUid() const;

private:
    static int newUID;

    const int uid;
    std::string title;
    std::string text;
    AndOrTree<LexicalPair> *tree;
};

#endif // CONTENTTEMPLATE_H
