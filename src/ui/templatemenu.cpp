#include "templatemenu.h"
#include "savemenu.h"

TemplateMenu::TemplateMenu(QWidget *parent, QString templateName) : QWidget(parent)
{
    parent->setWindowTitle("Template Menu");
    setTemplateName(templateName);

    // menu
    menuBar = new QMenuBar;
    backAction = menuBar->addAction("&Back");
    connect(backAction, SIGNAL(triggered()), parent, SLOT(handleBackAction()));
    saveAction = menuBar->addAction("&Save");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(handleSaveAction()));
    deleteAction = menuBar->addAction("&Delete");
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(handleDeleteAction()));
    connect(deleteAction, SIGNAL(triggered()), parent, SLOT(handleBackAction()));

    // labels
    font.setPointSize(16);
    templateLabel = new QLabel("Template");
    templateLabel->setFont(font);
    templateLabel->setAlignment(Qt::AlignCenter);
    treeLabel = new QLabel("Tree");
    treeLabel->setFont(font);
    treeLabel->setAlignment(Qt::AlignCenter);

    // template text
    templateText = new QTextEdit;
    if(templateName.isNull()) {
        templateText->setPlainText("New Template");
    } else {
        Storage& storage = Storage::Instance();
        templateText->setPlainText(storage.loadTemplate(templateName));
    }
    font.setPointSize(14);
    templateText->setFont(font);

    // tree visualisation
    treeText = new QTextEdit("Tree");
    treeText->setFont(font);

    // layout
    mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(templateLabel);
    mainLayout->addWidget(templateText);
    mainLayout->addWidget(treeLabel);
    mainLayout->addWidget(treeText);
    setLayout(mainLayout);
}

void TemplateMenu::setTemplateName(QString templateName)
{
    this->templateName = templateName;
}

void TemplateMenu::handleSaveAction()
{
    if(templateName.isNull()) {
        SaveMenu *saveMenu = new SaveMenu(0, this);
        saveMenu->setWindowModality(Qt::ApplicationModal);
        saveMenu->show();
    } else {
        Storage& storage = Storage::Instance();
        storage.saveTemplate(templateName, templateText->toPlainText());
    }
}

void TemplateMenu::handleDeleteAction()
{
    Storage& storage = Storage::Instance();
    storage.deleteTemplate(templateName);
}
