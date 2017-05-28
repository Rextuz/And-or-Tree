#include "tasktemplate.h"
#include "serializer.h"
#include <time.h>

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
    if (tree == nullptr)
        return new Content("task!");

    int seed = time(nullptr);

    string content = ContentTemplate::fillTemplate(text, LexicalPair::getDictionary(tree->getRoot(), seed));
    string generatedAnswer = ContentTemplate::fillTemplate(answer, LexicalPair::getDictionary(tree->getRoot(), seed));
    return new Content(content + "\n" + generatedAnswer);
}

void TaskTemplate::read(const QJsonObject &json, const QString xml_filename)
{
    answer = json["answer"].toString().toUtf8().constData();
    readCommonData(json, xml_filename);
}

void TaskTemplate::write(QJsonObject &json, const QString xml_filename) const
{
    json["type"] = "task";
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    json["answer"] = QString::fromUtf8(answer.c_str());
    writeTree(tree, xml_filename);
}

std::string TaskTemplate::getAnswer() const
{
    return answer;
}

void TaskTemplate::setAnswer(const std::string &value)
{
    answer = value;
}

