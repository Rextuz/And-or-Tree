#ifndef TEMPLATEMENU_H
#define TEMPLATEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>

// displays current ContentTemplate (template of text + tree)
class TemplateMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMenu(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QMenuBar *menuBar;
    QAction *backAction, *saveAction, *deleteAction;
};

#endif // TEMPLATEMENU_H
