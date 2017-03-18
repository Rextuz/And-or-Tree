#include "tasktemplate.h"

TaskTemplate::TaskTemplate(std::string title) : ContentTemplate(title)
{

}

TaskTemplate::TaskTemplate(std::string title, std::string text, LexicalTree *tree)
    : ContentTemplate(title, text, tree)
{

}

Content *TaskTemplate::generateContent()
{
    return new Content("task!");
}

