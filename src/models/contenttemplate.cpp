#include "contenttemplate.h"

// init static variable
int ContentTemplate::newUID = 0;

ContentTemplate::ContentTemplate(std::string title) : uid(newUID++)
{
    this->title = title;
    text = "put text here";
    tree = NULL; // здесь нужно будет создавать изначальное дерево
}

ContentTemplate::ContentTemplate(std::string title, std::string text, AndOrTree<LexicalPair> *tree) : uid(newUID++)
{
    this->title = title;
    this->text = text;
    this->tree = tree;
}

ContentTemplate::~ContentTemplate()
{
    delete tree;
}

std::string ContentTemplate::getTitle() const
{
    return title;
}

std::string ContentTemplate::getText() const
{
    return text;
}

AndOrTree<LexicalPair> *ContentTemplate::getTree() const
{
    return tree;
}

int ContentTemplate::getUid() const
{
    return uid;
}

void ContentTemplate::read(const QJsonObject &json)
{
    //uid = json["uid"].toInt();

    title = json["title"].toString().toUtf8().constData();
    text = json["text"].toString().toUtf8().constData();
    QJsonObject treeObject = json["tree"].toObject();
    delete tree;
    tree = new AndOrTree<LexicalPair>(t_and);
    tree->read(treeObject);
}

void ContentTemplate::write(QJsonObject &json) const
{
    //json["uid"] = uid;
    json["type"] = "???"; /// TODO play with polymorphic serialization
    json["title"] = QString::fromUtf8(title.c_str());
    json["text"] = QString::fromUtf8(text.c_str());
    QJsonObject treeObject;
    tree->write(treeObject);
    json["tree"] = treeObject;
}

bool ContentTemplate::load(std::string filename)
{
    QFile loadFile(QString::fromUtf8(filename.c_str()));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    read(loadDoc.object());

    return true;
}

bool ContentTemplate::save(std::string filename) const
{
    QFile saveFile(QString::fromUtf8(filename.c_str()));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

