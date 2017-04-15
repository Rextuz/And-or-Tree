#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");
    mainLayout = new QVBoxLayout;
    font.setPointSize(16);

    // label
    label = new QLabel("Templates");
    label->setFont(font);
    label->setMaximumHeight(40);
    label->setMinimumHeight(40);
    label->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(label);

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
            connect(button, SIGNAL (released()), parent, SLOT (handleExsistTemplateButton()));
            button->setFont(font);
            button->setFixedSize(240, 100);
            hLayout->addWidget(button);
        }
        if((count == 0) && (j < 4))
        {
            QPushButton *newButton = new QPushButton("+");
            connect(newButton, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
            newButton->setFont(font);
            newButton->setFixedSize(240, 100);
            hLayout->addWidget(newButton);
        }
        mainLayout->addLayout(hLayout);
    }

    // scroll area via inner widget
    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(1000, 800);
    scrollArea->setWidgetResizable(true);
    innerWidget = new QWidget(scrollArea);
    innerWidget->setLayout(mainLayout);
    scrollArea->setWidget(innerWidget);
}
