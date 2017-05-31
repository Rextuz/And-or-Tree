#include "templatemenu.h"
#include "customitem.h"

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
    connect(genButton, SIGNAL(released()), this, SLOT(handleGenerateAction()));

    // tree visualization
    scene = new QGraphicsScene;
    view = new QGraphicsView;
    drawTree(contentTemplate->getTree()->getRoot(),0,0);

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

void TemplateMenu::handleUpdateAction()
{
    scene = new QGraphicsScene;
    drawTree(contentTemplate->getTree()->getRoot(),0,0);
}

void TemplateMenu::drawTree(Node<LexicalPair> *tree, int x, int y)
{
    if(tree->getType() == t_leaf)
    {
        QString str = QString::fromStdString("(" + tree->getData()->getKey()+ ")" + " " + tree->getData()->getValue());
        if(str.length() > 20)
        {
            str.truncate(20);
            str.append("...");
        }
        QGraphicsTextItem *leafItem = scene->addText(str,font);
        leafItem->setPos(x+5,y+5);
        scene->addRect(x,y,200,50);
    }
    else
    {
        if(tree->getType() == t_and)
        {
            QGraphicsTextItem *item = scene->addText("and",font);
            item->setPos(x+5,y+5);
        }
        else
        {
            QGraphicsTextItem *item = scene->addText("or",font);
            item->setPos(x+10,y+5);
        }
        scene->addEllipse(x,y,50,50);

        int size = tree->size();
        if(size == 0)
            size = 1;
        CustomItem *item = new CustomItem(tree, this);
        item->setRect(x,y+70*size,50,50);
        scene->addItem(item);
        QGraphicsTextItem *plus = scene->addText("+",font);
        plus->setPos(x+15,y+5+70*size);
        scene->addLine(x+25,y+50,x+25,y+70*size);

        if(tree->hasChildren())
        {
            scene->addLine(x+50,y+25,x+70,y+25);
        }

        for (unsigned int i = 0, size = 0; i < tree->getChildren()->size(); i++)
        {
            if(i == 0)
            {
                drawTree(tree->getChild(i),x+70,y);
            }
            else
            {
                scene->addLine(x+25,y+25+70*(size+i),x+70,y+25+70*(size+i));
                drawTree(tree->getChild(i),x+70,y+70*(size+i));
            }
            size += tree->getChild(i)->size();
        }
    }

    view->setScene(scene);
}

void TemplateMenu::handleCustomItem(Node<LexicalPair> *tree)
{
    this->tree = tree;
    QPushButton *buttonSwitch = new QPushButton("switch");
    connect(buttonSwitch, SIGNAL (released()), this, SLOT (handleSwitchButton()));
    buttonSwitch->setFont(font);
    buttonSwitch->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
    QPushButton *buttonAnd = new QPushButton("and");
    connect(buttonAnd, SIGNAL (released()), this, SLOT (handleAndButton()));
    buttonAnd->setFont(font);
    buttonAnd->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
    QPushButton *buttonOr = new QPushButton("or");
    connect(buttonOr, SIGNAL (released()), this, SLOT (handleOrButton()));
    buttonOr->setFont(font);
    buttonOr->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
    QPushButton *buttonLeaf = new QPushButton("leaf");
    connect(buttonLeaf, SIGNAL (released()), this, SLOT (handleLeafButton()));
    buttonLeaf->setFont(font);
    buttonLeaf->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);
    QPushButton *buttonDelete = new QPushButton("delete");
    connect(buttonDelete, SIGNAL (released()), this, SLOT (handleDeleteButton()));
    buttonDelete->setFont(font);
    buttonDelete->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(buttonSwitch);
    layout->setAlignment(buttonSwitch, Qt::AlignCenter);
    layout->addWidget(buttonAnd);
    layout->setAlignment(buttonAnd, Qt::AlignCenter);
    layout->addWidget(buttonOr);
    layout->setAlignment(buttonOr, Qt::AlignCenter);
    layout->addWidget(buttonLeaf);
    layout->setAlignment(buttonLeaf, Qt::AlignCenter);
    layout->addWidget(buttonDelete);
    layout->setAlignment(buttonDelete, Qt::AlignCenter);

    customItemWindow = new QWidget(0);
    customItemWindow->setFixedSize(mainScreenSize.width()*0.15, mainScreenSize.height()*0.25);
    customItemWindow->setWindowModality(Qt::ApplicationModal);
    customItemWindow->setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    customItemWindow->setWindowTitle("Node menu");
    customItemWindow->setLayout(layout);
    customItemWindow->show();
}

void TemplateMenu::handleSwitchButton()
{
    if(tree->getType() == t_and)
    {
        tree->setType(t_or);
    }
    else
    {
        tree->setType(t_and);
    }
    handleUpdateAction();
    customItemWindow->close();
}

void TemplateMenu::handleAndButton()
{
    contentTemplate->getTree()->addNode(tree, t_and);
    handleUpdateAction();
    customItemWindow->close();
}

void TemplateMenu::handleOrButton()
{
    contentTemplate->getTree()->addNode(tree, t_or);
    handleUpdateAction();
    customItemWindow->close();
}

void TemplateMenu::handleLeafButton()
{
    customItemWindow->close();

    QLabel *keyLabel = new QLabel("Enter key:");
    keyLabel->setFont(font);
    QLabel *valueLabel = new QLabel("Enter value:");
    valueLabel->setFont(font);

    key = new QTextEdit;
    key->setFont(font);
    key->setFixedSize(mainScreenSize.width()*0.05, mainScreenSize.height()*0.04);
    value = new QTextEdit;
    value->setFont(font);
    value->setFixedSize(mainScreenSize.width()*0.2, mainScreenSize.height()*0.04);

    QPushButton *button = new QPushButton("add");
    connect(button, SIGNAL (released()), this, SLOT (handleAddButton()));
    button->setFont(font);
    button->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(keyLabel);
    vLayout->setAlignment(keyLabel, Qt::AlignCenter);
    vLayout->addWidget(key);
    vLayout->setAlignment(key, Qt::AlignCenter);
    hLayout->addLayout(vLayout);

    vLayout = new QVBoxLayout;
    vLayout->addWidget(valueLabel);
    vLayout->setAlignment(valueLabel, Qt::AlignCenter);
    vLayout->addWidget(value);
    vLayout->setAlignment(value, Qt::AlignCenter);
    hLayout->addLayout(vLayout);

    vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addWidget(button);
    vLayout->setAlignment(button, Qt::AlignRight);

    leafWindow = new QWidget(0);
    leafWindow->setFixedSize(mainScreenSize.width()*0.3, mainScreenSize.height()*0.2);
    leafWindow->setWindowModality(Qt::ApplicationModal);
    leafWindow->setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    leafWindow->setWindowTitle("Leaf menu");
    leafWindow->setLayout(vLayout);
    leafWindow->show();
}

void TemplateMenu::handleAddButton()
{
    contentTemplate->getTree()->addLeaf(tree, new LexicalPair(key->toPlainText().toUtf8().constData(),value->toPlainText().toUtf8().constData()));
    handleUpdateAction();
    leafWindow->close();
}

void TemplateMenu::handleDeleteButton()
{
    if(tree->getParent() != nullptr)
    {
        tree->deleteSelf();
        handleUpdateAction();
    }
    customItemWindow->close();
}
