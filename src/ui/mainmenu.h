#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

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
};

#endif // MAINMENU_H
