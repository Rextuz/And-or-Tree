#include "tasktemplate.h"

TaskTemplate::TaskTemplate(std::string title) : ContentTemplate(title)
{

}

TaskTemplate::TaskTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
    : ContentTemplate(title, text, tree)
{

}

Content *TaskTemplate::generateContent()
{
    return new Content("task!");
}

void TaskTemplate::read(const QJsonObject &json)
{
    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    QJsonObject treeObject = json["tree"].toObject();
    delete tree;
    tree = new AndOrTree<LexicalPair>(t_and);
    tree->read(treeObject);
}

void TaskTemplate::write(QJsonObject &json) const
{
    json["type"] = "task";
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    QJsonObject treeObject;
    tree->write(treeObject);
    json["tree"] = treeObject;
}

