#include "savemenu.h"

SaveMenu::SaveMenu(QWidget *parent, MainWindow *mainWindow) : QWidget(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    setWindowTitle("New Template");
    setFixedSize(500, 200);
    this->mainWindow = mainWindow;

    // labels
    font.setPointSize(14);
    label = new QLabel("Enter the name of the template:");
    label->setFont(font);
    label2 = new QLabel("Select the type of the template:");
    label2->setFont(font);

    // text area
    templateName = new QTextEdit;
    templateName->setFont(font);
    templateName->setMaximumHeight(35);

    // combo box
    cb = new QComboBox;
    cb->addItem("Joke");
    cb->addItem("Task");
    cb->setFixedSize(100, 30);

    // button
    button = new QPushButton("save");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));
    button->setFont(font);
    button->setFixedSize(100, 50);

    // layout
    layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->setAlignment(label, Qt::AlignCenter);
    layout->addWidget(templateName);
    layout->setAlignment(templateName, Qt::AlignCenter);
    layout->addWidget(label2);
    layout->setAlignment(label2, Qt::AlignCenter);
    layout->addWidget(cb);
    layout->setAlignment(cb, Qt::AlignCenter);
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignRight);
    setLayout(layout);
}

void SaveMenu::handleButton()
{
    QString string = templateName->toPlainText();
    string.truncate(20);
    mainWindow->handleNewTemplateButton(string, cb->currentIndex()==0 ? MainWindow::Type::Joke : MainWindow::Type::Task);
    close();
}
