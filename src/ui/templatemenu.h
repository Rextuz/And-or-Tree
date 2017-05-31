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
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <typeinfo>

#include "src/logic/storage.h"
#include "src/models/contenttemplate.h"

class TemplateMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMenu(QWidget *parent, ContentTemplate* contentTemplate);
    void setTemplateName(QString templateName);
    void handleCustomItem(Node<LexicalPair> *tree);

private slots:
    void handleSaveAction();
    void handleDeleteAction();
    void handleGenerateAction();
    void handleUpdateAction();
    void handleSwitchButton();
    void handleAndButton();
    void handleOrButton();
    void handleLeafButton();
    void handleDeleteButton();
    void handleAddButton();

private:
    QVBoxLayout *mainLayout, *vLayout;
    QHBoxLayout *hLayout;
    QMenuBar *menuBar;
    QAction *backAction, *saveAction, *deleteAction;
    QTextEdit *templateText, *answerText, *key, *value;
    QLabel *templateLabel, *treeLabel, *answerLabel;
    QPushButton *genButton;
    QFont font;
    QDesktopWidget desktopWidget;
    QRect mainScreenSize;
    QMessageBox messageBox;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *customItemWindow, *leafWindow;
    ContentTemplate *contentTemplate;
    Node<LexicalPair> *tree;
    LexicalPair *pair;

    void drawTree(Node<LexicalPair> *tree, int x, int y);
};

#endif // TEMPLATEMENU_H
