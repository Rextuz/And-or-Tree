#ifndef JOKETEMPLATE_H
#define JOKETEMPLATE_H

#include "contenttemplate.h"
#include "content.h"

class JokeTemplate : public ContentTemplate
{
public:
    JokeTemplate(std::string title);
    JokeTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree);

    Content* generateContent();

    void read(const QJsonObject &json, const QString xml_filename);
    void write(QJsonObject &json, const QString xml_filename) const;
};

#endif // JOKETEMPLATE_H
