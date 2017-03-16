#include "contenttemplate.h"

// init static variable
int ContentTemplate::newUID = 0;

ContentTemplate::ContentTemplate() : uid(newUID++)
{
    title = "noname";
    text = "put text here";
    tree = NULL; // здесь нужно будет создавать изначальное дерево
}

ContentTemplate::ContentTemplate(std::string title, std::string text, LexicalTree *tree) : uid(newUID++)
{
    this->title = title;
    this->text = text;
    this->tree = tree;
}

std::string ContentTemplate::getTitle() const
{
    return title;
}

std::string ContentTemplate::getText() const
{
    return text;
}

LexicalTree *ContentTemplate::getTree() const
{
    return tree;
}

int ContentTemplate::getUid() const
{
    return uid;
}

