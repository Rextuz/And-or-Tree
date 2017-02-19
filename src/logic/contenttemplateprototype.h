#ifndef CONTENTTEMPLATEPROTOTYPE_H
#define CONTENTTEMPLATEPROTOTYPE_H

#include <QObject>

// abstract class
// <Prototype pattern>
class ContentTemplatePrototype : public QObject
{
    Q_OBJECT
public:
    explicit ContentTemplatePrototype(QObject *parent = 0);

signals:

public slots:
};

#endif // CONTENTTEMPLATEPROTOTYPE_H
