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
        QFile::copy(":/resource/templates/Apples.xml", "templates/Apples.xml");
        QFile::copy(":/resource/templates/Chest.xml", "templates/Chest.xml");
        QFile::copy(":/resource/templates/Дорога домой.json", "templates/Дорога домой.json");
        QFile::copy(":/resource/templates/Дорога домой.xml", "templates/Дорога домой.xml");
    }

    dir.cd("templates");

    QFileInfoList list = dir.entryInfoList(QStringList() << "*.json", QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    templates.clear();
    for(int i = 0; i < list.size(); ++i) {
        templates.push_back(list.at(i).fileName().split(".").first());
    }
}

// return NULL if couldn't load
ContentTemplate* Storage::loadTemplateByName(QString name)
{
    QString xml_name;
    name.prepend("templates/");
    xml_name = name;
    xml_name.append(".xml");
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

    contentTemplate->read(json, xml_name);

    return contentTemplate;
}

bool Storage::saveTemplate(ContentTemplate *contentTemplate) const
{
    QString name = QString::fromUtf8(contentTemplate->getTitle().c_str());
    QString xml_name;
    name.prepend("templates/");
    xml_name = name;
    xml_name.append(".xml");
    name.append(".json");
    QFile saveFile(name);

    saveFile.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    contentTemplate->write(gameObject, xml_name);
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
