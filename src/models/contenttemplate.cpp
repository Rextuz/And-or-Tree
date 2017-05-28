#include "contenttemplate.h"
#include "serializer.h"

ContentTemplate::ContentTemplate(std::string title)
{
    this->title = title;
    text = "put text here";
    tree = new AndOrTree<LexicalPair>(t_and);
}

ContentTemplate::ContentTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
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

void ContentTemplate::setText(const std::string &value)
{
    text = value;
}

string ContentTemplate::fillTemplate(string text, map<string, string> dictionary) {
    string filledText = "";
    QString textUtf8 = QString::fromStdString(text);

    for (int i = 0; i < textUtf8.length() - 2; i++) {
        if (textUtf8.at(i) == '(')
            if (textUtf8.at(i + 2) == ')') {
                QString key1 = "";
                key1 += textUtf8.at(i);
                key1 += textUtf8.at(i + 1);
                key1 += textUtf8.at(i + 2);
                QString key2 = "";
                key2 += textUtf8.at(i + 1);
                string stdkey = key2.toStdString();
                textUtf8.replace(key1, QString::fromStdString(dictionary[stdkey]));
            }
    }

    return filledText = textUtf8.toStdString();
}

ContentTemplate::readCommonData(const QJsonObject &json, const QString xml_filename)
{
    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    delete tree;
    tree = readTree(xml_filename);
}
