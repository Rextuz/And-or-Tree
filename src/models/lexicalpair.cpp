#include "lexicalpair.h"

LexicalPair::LexicalPair(string key, string value)
{
    this->key.assign(key);
    this->value.assign(value);
}

string LexicalPair::getKey()
{
    return key;
}

string LexicalPair::getValue()
{
    return value;
}
