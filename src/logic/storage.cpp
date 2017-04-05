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
    for(int i = 0; i < templates.size(); ++i) {
        qDebug() << templates[i];
    }
}

QString Storage::loadTemplate(QString name)
{
    name.prepend("templates/");
    name.append(".txt");
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return NULL;

    QTextStream in(&file);
    in.setCodec(QTextCodec::codecForName("UTF-8"));
    QString content;
    while (!in.atEnd()) {
        QString line = in.readLine();
        content.append(line);
    }

    return content;
}

QString Storage::getTemplate(int id)
{
    return templates[id];
}

int Storage::getSize()
{
    return templates.size();
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
