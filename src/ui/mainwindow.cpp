#include "mainwindow.h"
#include "savemenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    mainScreenSize = desktopWidget.screenGeometry(desktopWidget.primaryScreen());
    setFixedSize(mainScreenSize.width()*0.8, mainScreenSize.height()*0.8);

    // for message box
    font.setFamily("Segoe UI Light");
    font.setPointSize(mainScreenSize.height()*0.013);
    messageBox.setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    messageBox.setWindowTitle("Error");
    messageBox.setIcon(QMessageBox::Critical);
    messageBox.setFont(font);

    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleExistTemplateButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString title = button->text();

    // try to load template
    Storage& storage = Storage::Instance();
    ContentTemplate* data = storage.loadTemplateByName(title);
    if(data != NULL){
        templateMenu = new TemplateMenu(this, data);
        setCentralWidget(templateMenu);
    }
    else{
        messageBox.setText("Template doesn`t exists!");
        messageBox.exec();
    }
}

void MainWindow::handleNewTemplateButton(QString name, MainWindow::Type type)
{
    if(name.length() < 1){
        messageBox.setText("Invalid template name!");
        messageBox.exec();
        handleNewTemplateButton();
    }
    else{
        Storage& storage = Storage::Instance();
        if(storage.loadTemplateByName(name) != NULL){
            messageBox.setText("Template with this name already exists!");
            messageBox.exec();
            handleNewTemplateButton();
        }
        else{
            ContentTemplate* newTemplate;
            switch(type){
                case Type::Joke:
                    newTemplate = jokeTemplateCreator.createTemplate(name.toUtf8().constData());
                    break;
                case Type::Task:
                    newTemplate = taskTemplateCreator.createTemplate(name.toUtf8().constData());
                    break;
            }

            templateMenu = new TemplateMenu(this, newTemplate);
            setCentralWidget(templateMenu);
        }
    }
}

void MainWindow::handleNewTemplateButton()
{
    SaveMenu *saveMenu = new SaveMenu(0, this);
    saveMenu->setWindowModality(Qt::ApplicationModal);
    saveMenu->show();
}

void MainWindow::handleBackAction()
{
    /// TODO modal window DO YOU WANT TO SAVE FILE?

    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}
