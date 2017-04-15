#include "storage.h"

Storage &Storage::Instance()
{
    static Storage s;
    return s;
}

void Storage::reloadList()
{
    QDir dir;
    if(!QDir("templates").exists()) {
        dir.mkdir("templates");
        QFile::copy(":/resource/templates/Apples.json", "templates/Apples.json");
        QFile::copy(":/resource/templates/Chest.json", "templates/Chest.json");
    }

    dir.cd("templates");

    QFileInfoList list = dir.entryInfoList(QStringList() << "*.json", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    templates.clear();
    for(int i = 0; i < list.size(); ++i) {
        templates.push_back(list.at(i).fileName().split(".").first());
    }

    std::cout << "Templates:" << std::endl;
    for(unsigned int i = 0; i < templates.size(); ++i) {
        qDebug() << templates[i];
    }
}

// return NULL if couldn't load
ContentTemplate* Storage::loadTemplate(QString name)
{
    name.prepend("templates/");
    name.append(".json");
    QFile loadFile(name);

    loadFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return NULL;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonObject json = loadDoc.object();

    std::string type = json["type"].toString().toUtf8().constData();
    ContentTemplate* contentTemplate;
    if(type == "joke"){
        contentTemplate = new JokeTemplate("???");
    }
    else if(type == "task"){
        contentTemplate = new TaskTemplate("???");
    }
    else{
        contentTemplate = NULL;
    }

    contentTemplate->read(json);

    return contentTemplate;
}

bool Storage::saveTemplate(ContentTemplate *contentTemplate) const
{
    QString name = QString::fromUtf8(contentTemplate->getTitle().c_str());
    name.prepend("templates/");
    name.append(".json");
    QFile saveFile(name);

    saveFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    contentTemplate->write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

bool Storage::deleteTemplate(QString name)
{
    templates.erase(std::remove(templates.begin(), templates.end(), name), templates.end());
    QDir("templates").remove(name.append(".json"));
    return true;
}

QString Storage::getTemplateName(int id)
{
    return templates[id];
}

int Storage::getSize()
{
    return (int)templates.size();
}

Storage::Storage()
{
    reloadList();
}
