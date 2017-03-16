#ifndef CONTENTTEMPLATE_H
#define CONTENTTEMPLATE_H

#include "lexicaltree.h"
#include <string>

// contains a template of text and a tree
class ContentTemplate
{
public:
    ContentTemplate();
    ContentTemplate(std::string title, std::string text, LexicalTree* tree);

    std::string getTitle() const;
    std::string getText() const;
    LexicalTree *getTree() const;
    int getUid() const;

private:
    static int newUID;

    const int uid;
    std::string title;
    std::string text;
    LexicalTree *tree;
};

#endif // CONTENTTEMPLATE_H
