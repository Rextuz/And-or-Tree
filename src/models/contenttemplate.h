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
    ~ContentTemplate();

    virtual Content* generateContent() = 0;

    std::string getTitle() const;
    std::string getText() const;
    AndOrTree<LexicalPair> *getTree() const;
    int getUid() const;

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    bool load(std::string filename);
    bool save(std::string filename) const;

private:
    static int newUID;

    const int uid;
    std::string title;
    std::string text;
    AndOrTree<LexicalPair> *tree;
};

#endif // CONTENTTEMPLATE_H
