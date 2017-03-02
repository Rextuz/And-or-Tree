#ifndef TEMPLATEMENU_H
#define TEMPLATEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QTextEdit>
#include <QLabel>

// displays current ContentTemplate (template of text + tree)
class TemplateMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMenu(QWidget *parent = 0);

private slots:
    void handleSaveAction();
    void handleDeleteAction();

private:
    QVBoxLayout *mainLayout;
    QMenuBar *menuBar;
    QAction *backAction, *saveAction, *deleteAction;
    QTextEdit *templateText, *treeText;
    QLabel *templateLabel, *treeLabel;
};

#endif // TEMPLATEMENU_H
