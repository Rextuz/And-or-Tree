#include "joketemplate.h"
#include "serializer.h"

JokeTemplate::JokeTemplate(std::string title) : ContentTemplate(title)
{

}

JokeTemplate::JokeTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
    : ContentTemplate(title, text, tree)
{

}

Content *JokeTemplate::generateContent()
{
    return new Content("joke!");
}

void JokeTemplate::read(const QJsonObject &json, const QString xml_filename)
{
    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    QJsonObject treeObject = json["tree"].toObject();
    delete tree;
    tree = readTree(xml_filename);
}

void JokeTemplate::write(QJsonObject &json, const QString xml_filename) const
{
    json["type"] = "joke";
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    writeTree(tree, xml_filename);
}

