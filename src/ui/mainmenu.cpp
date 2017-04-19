#include "mainmenu.h"

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    parent->setWindowTitle("Main Menu");
    mainLayout = new QVBoxLayout;

    // font
    font.setPointSize(dw.height()*0.015);
    font.setFamily("Segoe UI Light");

    // label
    label = new QLabel("Templates");
    label->setFont(font);
    label->setMaximumHeight(dw.height()*0.04);
    label->setMinimumHeight(dw.height()*0.04);
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
            button->setFixedSize(dw.width()*0.15, dw.height()*0.1);
            hLayout->addWidget(button);
        }
        if((count == 0) && (j < 4))
        {
            QPushButton *newButton = new QPushButton("+");
            connect(newButton, SIGNAL (released()), parent, SLOT (handleNewTemplateButton()));
            newButton->setFont(font);
            newButton->setFixedSize(dw.width()*0.15, dw.height()*0.1);
            hLayout->addWidget(newButton);
        }
        mainLayout->addLayout(hLayout);
    }

    // scroll area via inner widget
    scrollArea = new QScrollArea(this);
    scrollArea->setFixedSize(dw.width()*0.8, dw.height()*0.8);
    scrollArea->setWidgetResizable(true);
    innerWidget = new QWidget(scrollArea);
    innerWidget->setLayout(mainLayout);
    scrollArea->setWidget(innerWidget);
}
