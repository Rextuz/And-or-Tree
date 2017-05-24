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

    std::string getTitle() const;
    std::string getText() const;
    void setText(const std::string &value);
    AndOrTree<LexicalPair> *getTree() const;
    int getUid() const;

    virtual Content* generateContent() = 0;

    virtual void read(const QJsonObject &json, const QString xml_filename) = 0;
    virtual void write(QJsonObject &json, const QString xml_filename) const = 0;

protected:
    const int uid;
    std::string title;
    std::string text;
    AndOrTree<LexicalPair> *tree;

private:
    static int newUID;
    ContentTemplate(ContentTemplate const&);
    ContentTemplate& operator= (ContentTemplate const&);

};

#endif // CONTENTTEMPLATE_H
