#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication::setStyle("fusion");   // nowoczesny styl Qt
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}
