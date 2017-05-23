#include "templatemenu.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsItem>
#include <typeinfo>

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

    // tree visualization
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsTextItem *andItem = scene->addText("and",font);
    andItem->setPos(5,5);
    scene->addEllipse(0,0,50,50);
    scene->addLine(50,25,65,25);
    scene->addLine(25,50,25,445);
    scene->addLine(25,165,65,165);
    scene->addLine(25,445,70,445);
    QGraphicsTextItem *orItem = scene->addText("or",font);
    orItem->setPos(75,5);
    scene->addEllipse(65,0,50,50);
    scene->addLine(115,25,140,25);
    scene->addLine(90,50,90,95);
    scene->addLine(90,95,140,95);
    QGraphicsTextItem *leafItem = scene->addText("(А) Кэт",font);
    leafItem->setPos(145,5);
    scene->addRect(140,0,150,50);
    QGraphicsTextItem *leafItem2 = scene->addText("(А) Маша",font);
    leafItem2->setPos(145,75);
    scene->addRect(140,70,150,50);
    QGraphicsTextItem *orItem2 = scene->addText("or",font);
    orItem2->setPos(75,145);
    scene->addEllipse(65,140,50,50);
    scene->addLine(115,165,140,165);
    scene->addLine(90,190,90,305);
    scene->addLine(90,305,140,305);
    QGraphicsTextItem *andItem2 = scene->addText("and",font);
    andItem2->setPos(145,145);
    scene->addEllipse(140,140,50,50);
    scene->addLine(190,165,210,165);
    scene->addLine(165,190,165,235);
    scene->addLine(165,235,210,235);
    QGraphicsTextItem *leafItem3 = scene->addText("(B) Штирлицу",font);
    leafItem3->setPos(215,145);
    scene->addRect(210,140,150,50);
    QGraphicsTextItem *leafItem4 = scene->addText("(С) Штирлиц",font);
    leafItem4->setPos(215,215);
    scene->addRect(210,210,150,50);
    QGraphicsTextItem *andItem3 = scene->addText("and",font);
    andItem3->setPos(145,285);
    scene->addEllipse(140,280,50,50);
    scene->addLine(190,305,210,305);
    scene->addLine(165,330,165,375);
    scene->addLine(165,375,210,375);
    QGraphicsTextItem *leafItem5 = scene->addText("(B) Пете",font);
    leafItem5->setPos(215,285);
    scene->addRect(210,280,150,50);
    QGraphicsTextItem *leafItem6 = scene->addText("(С) Петя",font);
    leafItem6->setPos(215,355);
    scene->addRect(210,350,150,50);
    QGraphicsTextItem *leafItem7 = scene->addText("(E) лежало",font);
    leafItem7->setPos(75,425);
    scene->addRect(70,420,150,50);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);

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
