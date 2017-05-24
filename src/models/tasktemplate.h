#ifndef TASKTEMPLATE_H
#define TASKTEMPLATE_H

#include "contenttemplate.h"
#include "content.h"

class TaskTemplate : public ContentTemplate
{
public:
    TaskTemplate(std::string title);
    TaskTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree);

    std::string getAnswer() const;
    void setAnswer(const std::string &value);

    Content* generateContent();

    void read(const QJsonObject &json, const QString xml_filename);
    void write(QJsonObject &json, const QString xml_filename) const;

private:
    std::string answer;
};

#endif // TASKTEMPLATE_H
