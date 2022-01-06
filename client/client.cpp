//
// Created by stefan on 06.01.2022.
//
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char * argv[]){

    QApplication app(argc, argv);
    MainWindow w;
    w.init();
    w.resize(1300, 700);
    w.show();
    return app.exec();
}
