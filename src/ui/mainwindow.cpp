#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainMenu = new MainMenu();
    templateMenu = new TemplateMenu();
    setCentralWidget(mainMenu);
}

MainWindow::~MainWindow()
{

}
