#include "joketemplate.h"

JokeTemplate::JokeTemplate(std::string title) : ContentTemplate(title)
{

}

JokeTemplate::JokeTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree)
    : ContentTemplate(title, text, tree)
{

}

Content *JokeTemplate::generateContent()
{
    return new Content("joke!");
}

