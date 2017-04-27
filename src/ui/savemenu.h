#ifndef SAVEMENU_H
#define SAVEMENU_H

#include "mainwindow.h"
#include "qcombobox.h"

class SaveMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SaveMenu(QWidget *parent = 0, MainWindow *mainWindow = 0);

private slots:
    void handleButton();

private:
    MainWindow *mainWindow;
    QVBoxLayout *layout;
    QTextEdit *templateName;
    QLabel *label, *label2;
    QPushButton *button;
    QFont font;
    QDesktopWidget desktopWidget;
    QRect mainScreenSize;
    QComboBox* cb;
};

#endif // SAVEMENU_H
