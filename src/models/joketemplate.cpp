#include "joketemplate.h"

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

void JokeTemplate::read(const QJsonObject &json)
{
    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    QJsonObject treeObject = json["tree"].toObject();
    delete tree;
    tree = new AndOrTree<LexicalPair>(t_and);
    // TODO read tree
}

void JokeTemplate::write(QJsonObject &json) const
{
    json["type"] = "joke";
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    // TODO write tree
}

