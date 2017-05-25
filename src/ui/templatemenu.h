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
#include <typeinfo>

#include "src/logic/storage.h"
#include "src/models/contenttemplate.h"
#include "visualizator.h"

// displays current ContentTemplate (template of text + tree)
class TemplateMenu : public QWidget
{
    Q_OBJECT

public:
    explicit TemplateMenu(QWidget *parent, ContentTemplate* contentTemplate);
    void setTemplateName(QString templateName);

    static void handleCustomItem()
    {
        QDesktopWidget desktopWidget;
        QRect mainScreenSize = desktopWidget.screenGeometry(desktopWidget.primaryScreen());
        QFont font;
        font.setFamily("Segoe UI Light");
        font.setPointSize(mainScreenSize.height()*0.015);

        QPushButton *buttonAnd = new QPushButton("and");
        //connect(buttonAnd, SIGNAL (released()), this, SLOT (handleButton()));
        buttonAnd->setFont(font);
        buttonAnd->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
        QPushButton *buttonOr = new QPushButton("or");
        //connect(button, SIGNAL (released()), this, SLOT (handleButton()));
        buttonOr->setFont(font);
        buttonOr->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
        QPushButton *buttonLeaf = new QPushButton("leaf");
        //connect(button, SIGNAL (released()), this, SLOT (handleButton()));
        buttonLeaf->setFont(font);
        buttonLeaf->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
        QPushButton *buttonDelete = new QPushButton("delete");
        //connect(button, SIGNAL (released()), this, SLOT (handleButton()));
        buttonDelete->setFont(font);
        buttonDelete->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);

        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(buttonAnd);
        layout->setAlignment(buttonAnd, Qt::AlignCenter);
        layout->addWidget(buttonOr);
        layout->setAlignment(buttonOr, Qt::AlignCenter);
        layout->addWidget(buttonLeaf);
        layout->setAlignment(buttonLeaf, Qt::AlignCenter);
        layout->addWidget(buttonDelete);
        layout->setAlignment(buttonDelete, Qt::AlignCenter);

        QWidget *contentWindow = new QWidget(0);
        contentWindow->setFixedSize(mainScreenSize.width()*0.15, mainScreenSize.height()*0.2);
        contentWindow->setWindowModality(Qt::ApplicationModal);
        contentWindow->setWindowIcon(QIcon(":/resource/images/tree.jpg"));
        contentWindow->setWindowTitle("Node menu");
        contentWindow->setLayout(layout);
        contentWindow->show();
    }

private slots:
    void handleSaveAction();
    void handleDeleteAction();
    void handleGenerateAction();

private:
    QVBoxLayout *mainLayout, *vLayout;
    QHBoxLayout *hLayout;
    QMenuBar *menuBar;
    QAction *backAction, *saveAction, *deleteAction;
    QTextEdit *templateText, *answerText;
    QLabel *templateLabel, *treeLabel, *answerLabel;
    QPushButton* genButton;
    QFont font;
    QDesktopWidget desktopWidget;
    QRect mainScreenSize;
    QMessageBox messageBox;

    ContentTemplate* contentTemplate;
};

#endif // TEMPLATEMENU_H
