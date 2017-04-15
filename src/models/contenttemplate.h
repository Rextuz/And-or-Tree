#ifndef CONTENTTEMPLATE_H
#define CONTENTTEMPLATE_H

#include "content.h"
#include "andortree.h"
#include "lexicalpair.h"
#include <string>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

// contains a template of text and a tree
class ContentTemplate
{
public:
    ContentTemplate(std::string title);
    ContentTemplate(std::string title, std::string text, AndOrTree<LexicalPair>* tree);
    virtual ~ContentTemplate();

    virtual Content* generateContent() = 0;

    std::string getTitle() const;
    std::string getText() const;
    AndOrTree<LexicalPair> *getTree() const;
    int getUid() const;

    virtual void read(const QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) const = 0;

private:
    static int newUID;

protected:
    const int uid;
    std::string title;
    std::string text;
    AndOrTree<LexicalPair> *tree;
};

#endif // CONTENTTEMPLATE_H
