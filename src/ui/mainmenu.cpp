#include "mainmenu.h"
#include <QLabel>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent)
{
    // exmaple

    QPixmap pix(":/resource/images/tree.jpg");
    QPixmap p1(pix.scaled ( 300,300, Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    QLabel *lbl = new QLabel(this);
    lbl->setPixmap(p1);

    setFixedHeight(p1.height());
    setFixedWidth(p1.width());

}

