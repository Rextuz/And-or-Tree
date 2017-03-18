#ifndef CTCREATOR_H
#define CTCREATOR_H

#include "src/models/contenttemplate.h"
#include <string>

// Factory Method Pattern
class CTCreator
{
public:
    virtual ContentTemplate* createTemplate(std::string title) = 0;
};

#endif // CTCREATOR_H
