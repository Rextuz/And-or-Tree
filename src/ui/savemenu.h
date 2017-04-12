#ifndef SAVEMENU_H
#define SAVEMENU_H

#include "templatemenu.h"

class SaveMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SaveMenu(QWidget *parent = 0, TemplateMenu *templateMenu = 0);

private slots:
    void handleButton();

private:
    TemplateMenu *templateMenu;
    QVBoxLayout *layout;
    QTextEdit *templateName;
    QLabel *label;
    QPushButton *button;
    QFont font;
};

#endif // SAVEMENU_H
