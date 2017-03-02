#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainmenu.h"
#include "templatemenu.h"

// main windows displays either MainMenu widget or SingleJokeMenu widget
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void handleExsistTemplateButton();
    void handleNewTemplateButton();
    void handleBackAction();
    void handleSaveAction();
    void handleDeleteAction();

private:
    MainMenu* mainMenu;
    TemplateMenu* templateMenu;
};

#endif // MAINWINDOW_H
