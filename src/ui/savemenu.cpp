#include "savemenu.h"

SaveMenu::SaveMenu(QWidget *parent, MainWindow *mainWindow) : QWidget(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    setWindowTitle("New Template");
    mainScreenSize = desktopWidget.screenGeometry(desktopWidget.primaryScreen());
    setFixedSize(mainScreenSize.width()*0.25, mainScreenSize.height()*0.25);
    this->mainWindow = mainWindow;

    // font
    font.setFamily("Segoe UI Light");
    font.setPointSize(mainScreenSize.height()*0.013);

    // labels
    label = new QLabel("Enter the name of the template:");
    label->setFont(font);
    label2 = new QLabel("Select the type of the template:");
    label2->setFont(font);

    // text area
    templateName = new QTextEdit;
    templateName->setFont(font);
    templateName->setFixedSize(mainScreenSize.width()*0.2, mainScreenSize.height()*0.035);

    // combo box
    cb = new QComboBox;
    cb->addItem("Joke");
    cb->addItem("Task");
    cb->setFont(font);
    cb->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.03);

    // button
    button = new QPushButton("create");
    connect(button, SIGNAL (released()), this, SLOT (handleButton()));
    button->setFont(font);
    button->setFixedSize(mainScreenSize.width()*0.06, mainScreenSize.height()*0.04);

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
