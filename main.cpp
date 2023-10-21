#include <QMainWindow>
#include <QApplication>
#include <QLabel>

#include "mainwindow.h"
#include "game.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Game::dungeon;
    MainWindow w;
    w.setSize();
    QTimer::singleShot(40,&w,SLOT(show()));
    return a.exec();
}
