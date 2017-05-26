#ifndef TEST_ANDORTREE_H
#define TEST_ANDORTREE_H

#include <QObject>

class UTestTree : public QObject
{
    Q_OBJECT
public:
    explicit UTestTree(QObject *parent = 0);

private slots:
    void createTree();
    void addNode();
    void addLeaf();
    void deleteNode();
    void treeSize();

};

#endif // TEST_ANDORTREE_H
