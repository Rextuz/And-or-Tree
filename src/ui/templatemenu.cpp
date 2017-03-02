#include "templatemenu.h"

TemplateMenu::TemplateMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Template Menu");

    menuBar = new QMenuBar();
    backAction = menuBar->addAction(tr("Back"));
    connect(backAction, SIGNAL(triggered()), parent, SLOT(handleBackAction()));
    saveAction = menuBar->addAction("Save");
    connect(saveAction, SIGNAL(triggered()), parent, SLOT(handleSaveAction()));
    deleteAction = menuBar->addAction("Delete");
    connect(deleteAction, SIGNAL(triggered()), parent, SLOT(handleDeleteAction()));

    mainLayout = new QVBoxLayout();
    mainLayout->setMenuBar(menuBar);
    setLayout(mainLayout);
}
