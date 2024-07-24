#include "mainwindow.hpp"

#include <QApplication>

void cleanup();

int main(int argc, char *argv[])
{
    std::atexit(cleanup);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void cleanup()
{
    ;
}
