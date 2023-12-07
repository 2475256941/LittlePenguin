#include "mainscene.h"
#include<QScreen>
#include<QGuiApplication>
#include <QApplication>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScene w;
    srand(time(0));

    w.show();
    return a.exec();
}
