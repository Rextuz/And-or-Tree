#include "savemenu.h"

SaveMenu::SaveMenu(QWidget *parent, TemplateMenu *templateMenu) : QWidget(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    setWindowTitle("New Template");
    setFixedSize(500, 200);
    this->templateMenu = templateMenu;

    // labels
    font.setPointSize(14);
    label = new QLabel("Enter the name of the template:");
    label->setFont(font);

    // text area
    templateName = new QTextEdit;
    templateName->setFont(font);
    templateName->setMaximumHeight(35);

    // button
    button = new QPushButton("save");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));
    connect(button, SIGNAL (released()), templateMenu, SLOT (handleSaveAction()));
    button->setFont(font);
    button->setFixedSize(100, 50);

    // layout
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignCenter);
    layout->addWidget(templateName);
    layout->setAlignment(templateName, Qt::AlignCenter);
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignRight);
    setLayout(layout);
}

void SaveMenu::handleButton()
{
    QString string = templateName->toPlainText();
    string.truncate(20);
    templateMenu->setTemplateName(string);
    close();
}
