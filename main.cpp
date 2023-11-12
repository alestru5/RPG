#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <chrono>
#include "mainwindow.h"
#include "game.h"
#include<fstream>

int main(int argc, char *argv[]){
    srand(time(NULL));
    QApplication a(argc, argv);

    MainWindow w;
    w.setSize();
    QTimer::singleShot(40,&w,SLOT(show()));
    return a.exec();
}
