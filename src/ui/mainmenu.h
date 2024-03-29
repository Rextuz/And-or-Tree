#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QDesktopWidget>
#include "src/logic/storage.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QScrollArea *scrollArea;
    QWidget *innerWidget;
    QLabel *label;
    QFont font;
    QDesktopWidget desktopWidget;
    QRect mainScreenSize;
};

#endif // MAINMENU_H
