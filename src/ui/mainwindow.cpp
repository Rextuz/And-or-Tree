#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowIcon(QIcon(":/resource/images/tree.jpg"));
    resize(600, 600);
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

MainWindow::~MainWindow()
{

}

void MainWindow::handleExsistTemplateButton()
{
    templateMenu = new TemplateMenu(this);
    setCentralWidget(templateMenu);
}

void MainWindow::handleNewTemplateButton()
{
    templateMenu = new TemplateMenu(this);
    setCentralWidget(templateMenu);
}

void MainWindow::handleBackAction()
{
    mainMenu = new MainMenu(this);
    setCentralWidget(mainMenu);
}

void MainWindow::handleSaveAction()
{

}

void MainWindow::handleDeleteAction()
{

}
