#include "mainwindow.h"

#include <QApplication>


class MyClass : public MainWindow{

};

int main(int argc, char *argv[])
{
    qDebug() << "hello this is bella "  ;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MyClass obj ;
    emit obj.openFileSignal("hello");


    return a.exec();
}

