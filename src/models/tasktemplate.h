#ifndef TASKTEMPLATE_H
#define TASKTEMPLATE_H

#include "contenttemplate.h"
#include "content.h"

class TaskTemplate : public ContentTemplate
{
public:
    TaskTemplate(std::string title);
    TaskTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree);

    Content* generateContent();

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
};

#endif // TASKTEMPLATE_H
