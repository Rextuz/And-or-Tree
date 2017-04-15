#ifndef STORAGE_H
#define STORAGE_H

#include <QDebug>
#include <QTextCodec>
#include <QDir>
#include <vector>
#include <iostream>
#include "src/models/contenttemplate.h"
#include "src/models/tasktemplate.h"
#include "src/models/joketemplate.h"

class Storage
{
public:
    static Storage& Instance();

    void reloadList();
    void push(ContentTemplate* contentTemplate);
    void save(ContentTemplate* contentTemplate);
    void printData();
    QString getTemplateName(int id);
    int getSize();

    bool deleteTemplate(QString name);
    ContentTemplate* loadTemplate(QString name);
    bool saveTemplate(ContentTemplate* contentTemplate) const;

private:
    Storage();
    ~Storage() {}

    Storage(Storage const&);
    Storage& operator= (Storage const&);

    std::vector<QString> templates;
};

#endif // STORAGE_H
