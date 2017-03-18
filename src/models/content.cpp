#include "content.h"

Content::Content()
{
    str = "nothing";
}

Content::Content(const std::string &value)
{
    str = value;
}

std::string Content::getStr() const
{
    return str;
}

void Content::setStr(const std::string &value)
{
    str = value;
}

