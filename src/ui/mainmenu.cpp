#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");

    mainLayout = new QVBoxLayout();

    font.setPointSize(20);

    label = new QLabel("Templates");
    label->setFont(font);
    label->setMaximumHeight(40);
    label->setMinimumHeight(40);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

    Storage& storage = Storage::Instance();

    int count = storage.getSize();
    int rows = count / 4 + 1;

    for(int i = 0; i < rows; i++)
    {
        QHBoxLayout *hLayout = new QHBoxLayout();

        int j;

        for(j = 0; j < 4 && count > 0; j++, count--)
        {
            QPushButton *button = new QPushButton(storage.getTemplate(count - 1));
            connect(button, SIGNAL (released()), parent, SLOT (handleExsistTemplateButton()));
            button->setFont(font);
            button->setMinimumHeight(100);
            button->setMaximumWidth(200);
            hLayout->addWidget(button);
        }

        if((count == 0) && (j < 4))
        {
            QPushButton *newButton = new QPushButton("+");
            connect(newButton, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
            newButton->setFont(font);
            newButton->setMinimumHeight(100);
            newButton->setMaximumWidth(200);
            hLayout->addWidget(newButton);
        }

        mainLayout->addLayout(hLayout);
    }

    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(1000, 800);
    scrollArea->setWidgetResizable(true);

    innerWidget = new QWidget(scrollArea);
    innerWidget->setLayout(mainLayout);
    scrollArea->setWidget(innerWidget);
}
