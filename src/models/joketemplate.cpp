#include "joketemplate.h"
#include "serializer.h"
#include <time.h>

JokeTemplate::JokeTemplate(std::string title) : ContentTemplate(title)
{

}

JokeTemplate::JokeTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
    : ContentTemplate(title, text, tree)
{

}

Content *JokeTemplate::generateContent()
{
    if (tree == nullptr)
        return new Content("joke!");

    string content = ContentTemplate::fillTemplate(text, LexicalPair::getDictionary(tree->getRoot(), time(nullptr)));
    return new Content(content);
}

void JokeTemplate::read(const QJsonObject &json, const QString xml_filename)
{
    readCommonData(json, xml_filename);
}

void JokeTemplate::write(QJsonObject &json, const QString xml_filename) const
{
    json["type"] = "joke";
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    writeTree(tree, xml_filename);
}

