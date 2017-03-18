#include "tasktemplatecreator.h"
#include "src/models/tasktemplate.h"
#include "src/logic/storage.h"

TaskTemplateCreator::TaskTemplateCreator()
{

}

ContentTemplate *TaskTemplateCreator::createTemplate(std::string title)
{
    TaskTemplate* tt = new TaskTemplate(title);
    Storage& storage = Storage::Instance();
    storage.push(tt);
    return tt;
}

