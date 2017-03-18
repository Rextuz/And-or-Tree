#ifndef CONTENT_H
#define CONTENT_H

#include <string>

// joke or task
class Content
{
public:
    Content();
    Content(const std::string &value);

    std::string getStr() const;
    void setStr(const std::string &value);

private:
    std::string str;
};

#endif // CONTENT_H
