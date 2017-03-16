#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <iostream>
#include "src/models/contenttemplate.h"

class Storage
{
public:
    static Storage& Instance();

    void loadData();
    void push(ContentTemplate* ContentTemplate);
    void printData();

private:
    Storage() {}  // конструктор недоступен
    ~Storage() {} // и деструктор

    // необходимо запретить копирование
    Storage(Storage const&); // реализация не нужна
    Storage& operator= (Storage const&);  // и тут

    std::vector<ContentTemplate*> data;

};

#endif // STORAGE_H
