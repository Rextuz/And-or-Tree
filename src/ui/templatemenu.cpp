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
    QFont treeFont;
    treeFont.setFamily("Segoe UI Light");
    treeFont.setPointSize(16);
    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsTextItem *andItem = scene->addText("and",treeFont);
    andItem->setPos(5,5);
    scene->addEllipse(0,0,50,50);
    scene->addLine(50,25,65,25);
    scene->addLine(25,50,25,765);
    scene->addLine(25,235,65,235);
    scene->addLine(25,725,70,725);
    QGraphicsTextItem *orItem = scene->addText("or",treeFont);
    orItem->setPos(75,5);
    scene->addEllipse(65,0,50,50);
    scene->addLine(115,25,140,25);
    scene->addLine(90,50,90,140);
    scene->addLine(90,95,140,95);
    QGraphicsTextItem *leafItem = scene->addText("(А) Кэт",treeFont);
    leafItem->setPos(145,5);
    scene->addRect(140,0,150,50);
    QGraphicsTextItem *leafItem2 = scene->addText("(А) Маша",treeFont);
    leafItem2->setPos(145,75);
    scene->addRect(140,70,150,50);
    QGraphicsTextItem *plusItem = scene->addText("+",treeFont);
    plusItem->setPos(80,145);
    scene->addEllipse(65,140,50,50);
    QGraphicsTextItem *orItem2 = scene->addText("or",treeFont);
    orItem2->setPos(75,215);
    scene->addEllipse(65,210,50,50);
    scene->addLine(115,235,140,235);
    scene->addLine(90,260,90,630);
    scene->addLine(90,445,140,445);
    QGraphicsTextItem *andItem2 = scene->addText("and",treeFont);
    andItem2->setPos(145,215);
    scene->addEllipse(140,210,50,50);
    scene->addLine(190,235,210,235);
    scene->addLine(165,260,165,350);
    scene->addLine(165,305,210,305);
    QGraphicsTextItem *leafItem3 = scene->addText("(B) Штирлицу",treeFont);
    leafItem3->setPos(215,215);
    scene->addRect(210,210,150,50);
    QGraphicsTextItem *leafItem4 = scene->addText("(С) Штирлиц",treeFont);
    leafItem4->setPos(215,285);
    scene->addRect(210,280,150,50);
    QGraphicsTextItem *plusItem2 = scene->addText("+",treeFont);
    plusItem2->setPos(155,355);
    scene->addEllipse(140,350,50,50);
    QGraphicsTextItem *andItem3 = scene->addText("and",treeFont);
    andItem3->setPos(145,425);
    scene->addEllipse(140,420,50,50);
    scene->addLine(190,445,210,445);
    scene->addLine(165,470,165,560);
    scene->addLine(165,515,210,515);
    QGraphicsTextItem *leafItem5 = scene->addText("(B) Пете",treeFont);
    leafItem5->setPos(215,425);
    scene->addRect(210,420,150,50);
    QGraphicsTextItem *leafItem6 = scene->addText("(С) Петя",treeFont);
    leafItem6->setPos(215,495);
    scene->addRect(210,490,150,50);
    QGraphicsTextItem *plusItem3 = scene->addText("+",treeFont);
    plusItem3->setPos(155,565);
    scene->addEllipse(140,560,50,50);
    QGraphicsTextItem *plusItem4 = scene->addText("+",treeFont);
    plusItem4->setPos(80,635);
    scene->addEllipse(65,630,50,50);
    QGraphicsTextItem *leafItem7 = scene->addText("(E) лежало",treeFont);
    leafItem7->setPos(75,705);
    scene->addRect(70,700,150,50);
    QGraphicsTextItem *plusItem5 = scene->addText("+",treeFont);
    plusItem5->setPos(15,770);
    scene->addEllipse(0,765,50,50);

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
