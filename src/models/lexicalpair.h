#ifndef LEXICALPAIR_H
#define LEXICALPAIR_H

#include <string>
using std::string;

class LexicalPair
{
private:
    string key;
    string value;

public:
    LexicalPair(string key, string value);
    string getKey();
    string getValue();
};

#endif // LEXICALPAIR_H
