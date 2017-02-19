#ifndef CONTENTTEMPLATE_H
#define CONTENTTEMPLATE_H

#include "lexicaltree.h"

// contains a template of text and a tree
class ContentTemplate
{
public:
    ContentTemplate();

private:
    // template contains lexical tree
    LexicalTree tree;
};

#endif // CONTENTTEMPLATE_H
