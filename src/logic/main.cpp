#include "src/ui/mainwindow.h"
#include "test_andortree.h"
#include <QApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    /* Unit testing */
    QTest::qExec(new UTestTree, argc, argv);

    return a.exec();
}
