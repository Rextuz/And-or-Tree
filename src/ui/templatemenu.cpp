#include "templatemenu.h"
#include <QDebug>

TemplateMenu::TemplateMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Template Menu");

    menuBar = new QMenuBar();
    backAction = menuBar->addAction("&Back");
    connect(backAction, SIGNAL(triggered()), parent, SLOT(handleBackAction()));
    saveAction = menuBar->addAction("&Save");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(handleSaveAction()));
    deleteAction = menuBar->addAction("&Delete");
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(handleDeleteAction()));

    font.setPointSize(20);
    templateLabel = new QLabel("Template");
    templateLabel->setFont(font);
    templateLabel->setAlignment(Qt::AlignCenter);
    treeLabel = new QLabel("Tree");
    treeLabel->setFont(font);
    treeLabel->setAlignment(Qt::AlignCenter);
    font.setPointSize(14);
    templateText = new QTextEdit("Template");
    templateText->setFont(font);
    treeText = new QTextEdit("Tree");
    treeText->setFont(font);

    mainLayout = new QVBoxLayout();
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(templateLabel);
    mainLayout->addWidget(templateText);
    mainLayout->addWidget(treeLabel);
    mainLayout->addWidget(treeText);
    setLayout(mainLayout);
}

void TemplateMenu::handleSaveAction()
{
    QString text = templateText->toPlainText();
    qDebug() << text;
}

void TemplateMenu::handleDeleteAction()
{
    QString text = templateText->toPlainText();
    qDebug() << text;
}
