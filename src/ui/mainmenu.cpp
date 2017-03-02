#include "mainmenu.h"
#include <QGroupBox>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");

    QHBoxLayout *h1Layout = new QHBoxLayout;
    QPushButton *b1 = new QPushButton("A");
    QPushButton *b2 = new QPushButton("B");
    QPushButton *b3 = new QPushButton("C");
    h1Layout->addWidget(b1);
    h1Layout->addWidget(b2);
    h1Layout->addWidget(b3);

    QHBoxLayout *h2Layout = new QHBoxLayout;
    QPushButton *b4 = new QPushButton("D");
    QPushButton *b5 = new QPushButton("E");
    QPushButton *b6 = new QPushButton("+");
    connect(b6, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
    h2Layout->addWidget(b4);
    h2Layout->addWidget(b5);
    h2Layout->addWidget(b6);

    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(h1Layout);
    mainLayout->addLayout(h2Layout);
    setLayout(mainLayout);
}
