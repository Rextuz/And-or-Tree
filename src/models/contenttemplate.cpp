#include "contenttemplate.h"

// init static variable
int ContentTemplate::newUID = 0;

ContentTemplate::ContentTemplate(std::string title) : uid(newUID++)
{
    this->title = title;
    text = "put text here";
    tree = NULL; // здесь нужно будет создавать изначальное дерево
}

ContentTemplate::ContentTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree) : uid(newUID++)
{
    this->title = title;
    this->text = text;
    this->tree = tree;
}

ContentTemplate::~ContentTemplate()
{
    delete tree;
}

std::string ContentTemplate::getTitle() const
{
    return title;
}

std::string ContentTemplate::getText() const
{
    return text;
}

AndOrTree<LexicalPair> *ContentTemplate::getTree() const
{
    return tree;
}

int ContentTemplate::getUid() const
{
    return uid;
}
