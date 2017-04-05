#include "mainwindow.h"

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
    templateMenu = new TemplateMenu(this, button->text());
    setCentralWidget(templateMenu);
}

void MainWindow::handleNewTemplateButton()
{
    templateMenu = new TemplateMenu(this, NULL);
    setCentralWidget(templateMenu);
}

void MainWindow::handleBackAction()
{
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}
