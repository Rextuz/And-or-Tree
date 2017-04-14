#ifndef STORAGE_H
#define STORAGE_H

#include <QDebug>
#include <QTextCodec>
#include <QDir>
#include <vector>
#include <iostream>
#include "src/models/contenttemplate.h"

class Storage
{
public:
    static Storage& Instance();

    void loadList();
    QString loadTemplate(QString name);
    void saveTemplate(QString name, QString content);
    void deleteTemplate(QString name);
    void push(ContentTemplate* contentTemplate);
    void save(ContentTemplate* contentTemplate);
    void printData();
    QString getTemplate(int id);
    int getSize();

private:
    Storage();  // конструктор недоступен
    ~Storage() {} // и деструктор

    // необходимо запретить копирование
    Storage(Storage const&); // реализация не нужна
    Storage& operator= (Storage const&);  // и тут

    std::vector<QString> templates;
    std::vector<ContentTemplate*> data;

};

#endif // STORAGE_H
