#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");

    mainLayout = new QVBoxLayout();

    QFont font;
    font.setPointSize(12);

    label = new QLabel("Templates");
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    for(int i = 0; i < 5; i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();
        for(int j = 0; j < 4; j++)
        {
            QPushButton *b = new QPushButton("joke++");
            connect(b, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
            b->setMinimumHeight(70);
            b->setMinimumWidth(100);
            b->setFont(font);
            hLayout->addWidget(b);
        }
        mainLayout->addLayout(hLayout);
    }

    setLayout(mainLayout);
}
