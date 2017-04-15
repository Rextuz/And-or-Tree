#include "tasktemplate.h"

TaskTemplate::TaskTemplate(std::string title) : ContentTemplate(title)
{
    answer = "answer";
}

TaskTemplate::TaskTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
    : ContentTemplate(title, text, tree)
{
    answer = "answer";
}

Content *TaskTemplate::generateContent()
{
    return new Content("task!");
}

void TaskTemplate::read(const QJsonObject &json)
{
    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    answer = json["answer"].toString().toUtf8().constData();
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
    json["answer"] = QString::fromUtf8(answer.c_str());
    QJsonObject treeObject;
    tree->write(treeObject);
    json["tree"] = treeObject;
}

std::string TaskTemplate::getAnswer() const
{
    return answer;
}

void TaskTemplate::setAnswer(const std::string &value)
{
    answer = value;
}

