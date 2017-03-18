#ifndef JOKETEMPLATECREATOR_H
#define JOKETEMPLATECREATOR_H

#include "ctcreator.h"
#include "src/models/contenttemplate.h"

class JokeTemplateCreator : public CTCreator
{
public:
    JokeTemplateCreator();

    ContentTemplate* createTemplate(std::string title);
};

#endif // JOKETEMPLATECREATOR_H
