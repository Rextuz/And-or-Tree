#include "joketemplatecreator.h"
#include "src/models/joketemplate.h"
#include "src/logic/storage.h"

JokeTemplateCreator::JokeTemplateCreator()
{

}

ContentTemplate *JokeTemplateCreator::createTemplate(std::string title)
{
    JokeTemplate* jt = new JokeTemplate(title);
    return jt;
}

