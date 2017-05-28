#ifndef CONTENTTEMPLATE_H
#define CONTENTTEMPLATE_H

#include "content.h"
#include "andortree.h"
#include "lexicalpair.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>

#include <string>
using std::string;

#include <map>
using std::map;

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

    virtual Content* generateContent() = 0;

    virtual void read(const QJsonObject &json, const QString xml_filename) = 0;
    virtual void write(QJsonObject &json, const QString xml_filename) const = 0;

    static string fillTemplate(string text, map<string, string> dictionary);

protected:
    std::string title;
    std::string text;
    AndOrTree<LexicalPair> *tree;

    readCommonData(const QJsonObject &json, const QString xml_filename);

private:
    ContentTemplate(ContentTemplate const&);
    ContentTemplate& operator= (ContentTemplate const&);

};

#endif // CONTENTTEMPLATE_H
