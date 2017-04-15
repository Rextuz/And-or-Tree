#include "templatemenu.h"
#include "savemenu.h"

TemplateMenu::TemplateMenu(QWidget *parent, ContentTemplate* contentTemplate) : QWidget(parent)
{
    this->contentTemplate = contentTemplate;
    parent->setWindowTitle(QString::fromUtf8(contentTemplate->getTitle().c_str()));

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
    templateText->setPlainText(QString::fromUtf8(contentTemplate->getText().c_str()));

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

void TemplateMenu::handleSaveAction()
{
    contentTemplate->setText(templateText->toPlainText().toUtf8().constData());
    Storage& storage = Storage::Instance();
    bool status = storage.saveTemplate(contentTemplate);
    if(!status){
        ///TODO draw error message box
    }
}

void TemplateMenu::handleDeleteAction()
{
    Storage& storage = Storage::Instance();
    bool status = storage.deleteTemplate(QString::fromUtf8(contentTemplate->getTitle().c_str()));
    if(!status){
        ///TODO draw error message box
    }
}
