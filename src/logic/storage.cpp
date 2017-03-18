#include <iomanip>
#include <QDebug>
#include "storage.h"

Storage &Storage::Instance()
{
    // согласно стандарту, этот код ленивый и потокобезопасный
    static Storage s;
    return s;
}

void Storage::loadData()
{
    char* userDir = "C:\\Users\\Denis\\Documents\\AndOrTree\\data.cfg\n";
    qDebug() << "Config loaded from "<<userDir;
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
    for(unsigned int i=0; i<data.size(); ++i){
        std::cout << (i+1) << " element (uid="<<data[i]->getUid()<<"): " << data[i]->getTitle() << " - " << data[i]->getText() << "\n";
    }
}
