#include "templatemenu.h"

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

    // font
    font.setFamily("Segoe UI Light");
    font.setPointSize(dw.height()*0.015);

    // labels
    templateLabel = new QLabel("Template");
    templateLabel->setFont(font);
    templateLabel->setAlignment(Qt::AlignCenter);
    treeLabel = new QLabel("Tree");
    treeLabel->setFont(font);
    treeLabel->setAlignment(Qt::AlignCenter);

    // template text
    templateText = new QTextEdit;
    templateText->setPlainText(QString::fromUtf8(contentTemplate->getText().c_str()));
    templateText->setFont(font);

    // button
    genButton = new QPushButton;
    genButton->setIcon(QIcon(":/resource/images/gear.jpg"));
    genButton->setIconSize(QSize(dw.height()*0.1, dw.height()*0.1));
    connect(genButton, SIGNAL(clicked(bool)), this, SLOT(handleGenerateAction()));

    // tree visualisation
    treeText = new QTextEdit("Tree");
    treeText->setFont(font);

    // layout
    hLayout = new QHBoxLayout;

    vLayout = new QVBoxLayout;
    vLayout->addWidget(templateLabel);
    vLayout->addWidget(templateText);

    if(typeid(*contentTemplate) == typeid(TaskTemplate)) {
        answerLabel = new QLabel("Answer");
        answerLabel->setFont(font);
        answerLabel->setAlignment(Qt::AlignCenter);

        answerText = new QTextEdit;
        answerText->setPlainText(QString::fromUtf8(((TaskTemplate *)contentTemplate)->getAnswer().c_str()));
        answerText->setFont(font);

        vLayout->addWidget(answerLabel);
        vLayout->addWidget(answerText);
    }

    hLayout->addLayout(vLayout);

    vLayout = new QVBoxLayout;
    vLayout->addWidget(treeLabel);
    vLayout->addWidget(treeText);
    hLayout->addLayout(vLayout);

    hLayout->addWidget(genButton);

    mainLayout = new QVBoxLayout;
    mainLayout->setMenuBar(menuBar);
    mainLayout->addLayout(hLayout);
    setLayout(mainLayout);

    // for message box
    messageBox.setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    messageBox.setWindowTitle("Error");
    messageBox.setIcon(QMessageBox::Critical);
}

void TemplateMenu::handleSaveAction()
{
    contentTemplate->setText(templateText->toPlainText().toUtf8().constData());
    Storage& storage = Storage::Instance();
    bool status = storage.saveTemplate(contentTemplate);
    if(!status){
        font.setPointSize(dw.height()*0.013);
        messageBox.setFont(font);
        messageBox.setText("Template not saved!");
        messageBox.exec();
    }
}

void TemplateMenu::handleDeleteAction()
{
    Storage& storage = Storage::Instance();
    bool status = storage.deleteTemplate(QString::fromUtf8(contentTemplate->getTitle().c_str()));
    if(!status){
        font.setPointSize(dw.height()*0.013);
        messageBox.setFont(font);
        messageBox.setText("Template not deleted!");
        messageBox.exec();
    }
}

void TemplateMenu::handleGenerateAction()
{
    Content* content = contentTemplate->generateContent();

    font.setPointSize(dw.height()*0.015);

    QTextEdit *text = new QTextEdit;
    text->setPlainText(QString::fromUtf8(content->getStr().c_str()));
    text->setReadOnly(true);
    text->setFont(font);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(text);

    QWidget *contentWindow = new QWidget(0);
    contentWindow->setFixedSize(dw.width()*0.4, dw.height()*0.4);
    contentWindow->setWindowModality(Qt::ApplicationModal);
    contentWindow->setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    contentWindow->setWindowTitle("Generated content");
    contentWindow->setLayout(mainLayout);
    contentWindow->show();
}
