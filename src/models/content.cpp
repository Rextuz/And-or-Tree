#include "content.h"

Content::Content()
{

}

std::string Content::getStr() const
{
    return str;
}

void Content::setStr(const std::string &value)
{
    str = value;
}

