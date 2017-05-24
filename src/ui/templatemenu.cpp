#include "templatemenu.h"

TemplateMenu::TemplateMenu(QWidget *parent, ContentTemplate* contentTemplate) : QWidget(parent)
{
    mainScreenSize = desktopWidget.screenGeometry(desktopWidget.primaryScreen());
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
    font.setPointSize(mainScreenSize.height()*0.015);

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
    genButton->setIconSize(QSize(mainScreenSize.height()*0.1, mainScreenSize.height()*0.1));
    connect(genButton, SIGNAL(clicked(bool)), this, SLOT(handleGenerateAction()));

    // --------------------------- EXAMPLE -------------------------------
    AndOrTree<LexicalPair> *tree = new AndOrTree<LexicalPair>(t_and);

    Node<LexicalPair> *characters = tree->addNode(tree->getRoot(), t_or);
    Node<LexicalPair> *actions = tree->addNode(tree->getRoot(), t_and);
    Node<LexicalPair> *actions_what = tree->addNode(actions, t_and);
    Node<LexicalPair> *actions_where = tree->addNode(actions, t_or);

    // Populate with characters
    tree->addLeaf(characters, new LexicalPair("A", "Max"));
    tree->addLeaf(characters, new LexicalPair("A", "Denis"));
    tree->addLeaf(characters, new LexicalPair("A", "Efim"));

    // Populate with actions
    tree->addLeaf(actions_what, new LexicalPair("B", "Dance"));
    tree->addLeaf(actions_what, new LexicalPair("B", "Sing"));
    tree->addLeaf(actions_where, new LexicalPair("C", "At home"));
    tree->addLeaf(actions_where, new LexicalPair("C", "In the forest"));
    tree->addLeaf(actions_where, new LexicalPair("C", "In the bar"));
    // -------------------------------------------------------------------

    // tree visualization
    Visualizator *visualizator = new Visualizator(tree);
    QGraphicsView *view = visualizator->getView();

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
    vLayout->addWidget(view);
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
        font.setPointSize(mainScreenSize.height()*0.013);
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
        font.setPointSize(mainScreenSize.height()*0.013);
        messageBox.setFont(font);
        messageBox.setText("Template not deleted!");
        messageBox.exec();
    }
}

void TemplateMenu::handleGenerateAction()
{
    Content* content = contentTemplate->generateContent();

    font.setPointSize(mainScreenSize.height()*0.015);

    QTextEdit *text = new QTextEdit;
    text->setPlainText(QString::fromUtf8(content->getStr().c_str()));
    text->setReadOnly(true);
    text->setFont(font);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(text);

    QWidget *contentWindow = new QWidget(0);
    contentWindow->setFixedSize(mainScreenSize.width()*0.4, mainScreenSize.height()*0.4);
    contentWindow->setWindowModality(Qt::ApplicationModal);
    contentWindow->setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    contentWindow->setWindowTitle("Generated content");
    contentWindow->setLayout(mainLayout);
    contentWindow->show();
}
