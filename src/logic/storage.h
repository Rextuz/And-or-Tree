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

    void loadList();
    void push(ContentTemplate* contentTemplate);
    void save(ContentTemplate* contentTemplate);
    void printData();
    QString getTemplate(int id);
    int getSize();

    void deleteTemplate(QString name);
    QString loadTemplate(QString name);
    void saveTemplate(QString name, QString content);
    ContentTemplate* loadTemplate(std::string filename);
    bool saveTemplate(ContentTemplate* contentTemplate, std::string filename) const;

private:
    Storage();
    ~Storage() {}

    Storage(Storage const&);
    Storage& operator= (Storage const&);

    std::vector<QString> templates;
    std::vector<ContentTemplate*> data;

};

#endif // STORAGE_H
