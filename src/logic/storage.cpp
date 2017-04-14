#include "storage.h"

Storage &Storage::Instance()
{
    // согласно стандарту, этот код ленивый и потокобезопасный
    static Storage s;
    return s;
}

void Storage::loadList()
{
    QDir dir;
    if(!QDir("templates").exists()) {
        dir.mkdir("templates");
        QFile::copy(":/resource/templates/joke.txt", "templates/joke.txt");
        QFile::copy(":/resource/templates/Denis.txt", "templates/Denis.txt");
        QFile::copy(":/resource/templates/Max.txt", "templates/Max.txt");
        QFile::copy(":/resource/templates/test joke.txt", "templates/test joke.txt");
        QFile::copy(":/resource/templates/April Fools Day.txt", "templates/April Fools Day.txt");
    }

    dir.cd("templates");

    QFileInfoList list = dir.entryInfoList(QStringList() << "*.txt", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    for(int i = 0; i < list.size(); ++i) {
        templates.push_back(list.at(i).fileName().split(".").first());
    }

    std::cout << "Templates:" << std::endl;
    for(unsigned int i = 0; i < templates.size(); ++i) {
        qDebug() << templates[i];
    }
}

QString Storage::loadTemplate(QString name)
{
    name.prepend("templates/");
    name.append(".txt");
    QFile file(name);
    file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return NULL;

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    QString content;
    while (!in.atEnd()) {
        QString line = in.readLine();
        content.append(line + "\n");
    }
    content.chop(1);

    return content;
}

void Storage::saveTemplate(QString name, QString content)
{
    if(!(std::find(templates.begin(), templates.end(), name) != templates.end()))
        templates.push_back(name);
    name.prepend("templates/");
    name.append(".txt");
    QFile file(name);
    file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out.setCodec(QTextCodec::codecForName("UTF-8"));
    out << content;
}

void Storage::deleteTemplate(QString name)
{
    templates.erase(std::remove(templates.begin(), templates.end(), name), templates.end());
    QDir("templates").remove(name.append(".txt"));
}

QString Storage::getTemplate(int id)
{
    return templates[id];
}

int Storage::getSize()
{
    return (int)templates.size();
}

Storage::Storage()
{
    loadList();
}

void Storage::push(ContentTemplate *contentTemplate)
{
    data.push_back(contentTemplate);
}

void Storage::save(ContentTemplate *contentTemplate)
{
    std::cout << "Template '" << contentTemplate->getTitle()<<"' saved to disk" << "\n";
}

void Storage::printData()
{
    for(unsigned int i=0; i<data.size(); ++i) {
        std::cout << (i+1) << " element (uid="<<data[i]->getUid()<<"): " << data[i]->getTitle() << " - " << data[i]->getText() << "\n";
    }
}
