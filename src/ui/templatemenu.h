#ifndef TEMPLATEMENU_H
#define TEMPLATEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QDesktopWidget>
#include <QMessageBox>
#include "src/logic/storage.h"
#include "src/models/contenttemplate.h"

// displays current ContentTemplate (template of text + tree)
class TemplateMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMenu(QWidget *parent, ContentTemplate* contentTemplate);
    void setTemplateName(QString templateName);

private slots:
    void handleSaveAction();
    void handleDeleteAction();
    void handleGenerateAction();

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *hLayout;
    QMenuBar *menuBar;
    QAction *backAction, *saveAction, *deleteAction;
    QTextEdit *templateText, *treeText;
    QLabel *templateLabel, *treeLabel;
    QPushButton* genButton;
    QFont font;
    QDesktopWidget dw;
    QMessageBox messageBox;

    ContentTemplate* contentTemplate;
};

#endif // TEMPLATEMENU_H
