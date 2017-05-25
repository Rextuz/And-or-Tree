#include "mainmenu.h"
#include "qpainter.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");
    mainScreenSize = desktopWidget.screenGeometry(desktopWidget.primaryScreen());
    mainLayout = new QVBoxLayout;

    // font
    font.setPointSize(mainScreenSize.height()*0.015);
    font.setFamily("Segoe UI Light");
    font.setBold(true);

    //background
    qDebug()<<this->size();
    QPixmap bkgnd(":/resource/images/bg.jpg");
    //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    // buttons
    Storage& storage = Storage::Instance();
    storage.reloadList();
    int count = storage.getSize();
    int rows = count / 4 + 1;
    for(int i = 0; i < rows; i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout;
        int j;
        for(j = 0; j < 4 && count > 0; j++, count--)
        {
            QPushButton *button = new QPushButton(storage.getTemplateName(count - 1));
            connect(button, SIGNAL (released()), parent, SLOT (handleExistTemplateButton()));
            button->setFont(font);
            button->setFixedSize(mainScreenSize.width()*0.15, mainScreenSize.height()*0.15);
            button->setStyleSheet("QPushButton {border-image: url(:/resource/images/note.png);}");
            hLayout->addWidget(button);
        }
        if((count == 0) && (j < 4))
        {
            QPushButton *newButton = new QPushButton("+");
            connect(newButton, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
            newButton->setFont(font);
            newButton->setFixedSize(mainScreenSize.width()*0.15, mainScreenSize.height()*0.15);
            newButton->setStyleSheet("QPushButton {border-image: url(:/resource/images/note.png);}");
            hLayout->addWidget(newButton);
        }
        mainLayout->addLayout(hLayout);
    }

    // scroll area via inner widget
    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(mainScreenSize.width()*0.8, mainScreenSize.height()*0.8);
    scrollArea->setWidgetResizable(true);
    innerWidget = new QWidget(scrollArea);
    innerWidget->setLayout(mainLayout);
    scrollArea->setWidget(innerWidget);
}
