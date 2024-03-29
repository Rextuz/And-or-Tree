#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainmenu.h"
#include "templatemenu.h"
#include "src/logic/joketemplatecreator.h"
#include "src/logic/tasktemplatecreator.h"

// main windows displays either MainMenu widget or SingleJokeMenu widget
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum Type{Joke, Task};
    void handleNewTemplateButton(QString name, Type type);

private slots:
    void handleExistTemplateButton();
    void handleNewTemplateButton();
    void handleBackAction();

private:
    MainMenu *mainMenu;
    TemplateMenu *templateMenu;

    JokeTemplateCreator jokeTemplateCreator;
    TaskTemplateCreator taskTemplateCreator;

    QFont font;
    QDesktopWidget desktopWidget;
    QRect mainScreenSize;
    QMessageBox messageBox;
};

#endif // MAINWINDOW_H
