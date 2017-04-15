#include "mainwindow.h"
#include "src/ui/savemenu.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    setFixedSize(1000, 800);
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleExsistTemplateButton()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QString title = button->text();

    // try to load template
    Storage& storage = Storage::Instance();
    ContentTemplate* data = storage.loadTemplate(title);
    if(data != NULL){
        templateMenu = new TemplateMenu(this, data);
        setCentralWidget(templateMenu);
    }
    else{
        ///TODO draw error message box
    }
}

void MainWindow::handleNewTemplateButton(QString name, MainWindow::Type type)
{
    if(name.length() < 1){
        ///TODO draw error message box
    }
    else{
        /// TODO if template with such name exists -> draw error message box
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
