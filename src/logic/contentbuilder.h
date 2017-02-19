#ifndef CONTENTBUILDER_H
#define CONTENTBUILDER_H

#include <QObject>

// Abstract Builder
// <Builder pattern>
class ContentBuilder : public QObject
{
    Q_OBJECT
public:
    explicit ContentBuilder(QObject *parent = 0);

signals:

public slots:
};

#endif // CONTENTBUILDER_H
