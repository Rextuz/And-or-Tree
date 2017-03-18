#ifndef TASKTEMPLATECREATOR_H
#define TASKTEMPLATECREATOR_H

#include "ctcreator.h"
#include "src/models/contenttemplate.h"

class TaskTemplateCreator : public CTCreator
{
public:
    TaskTemplateCreator();

    ContentTemplate* createTemplate(std::string title);
};

#endif // TASKTEMPLATECREATOR_H
