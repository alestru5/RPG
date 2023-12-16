#include <QMainWindow>
#include <QApplication>
#include <QLabel>
#include <chrono>
#include<fstream>
#include <QTimer>
#include <thread>
#include <dlfcn.h>
#include <dirent.h>
#include <QSplashScreen>

#include "./graphics/mainwindow.h"
#include "./engine/game.h"


int main(int argc, char *argv[]){
    srand(time(NULL));
    QApplication a(argc, argv);
    QPixmap pixmap("/home/alestru/PetProjects/RPG/img/splash.png");
    QSize PicSize(512, 384);
    pixmap = pixmap.scaled(PicSize,Qt::KeepAspectRatio);
    QSplashScreen splash(pixmap, Qt::WindowStaysOnTopHint);
    splash.show();
    QTimer::singleShot(3000, &splash, &QWidget::close);

    MainWindow w;
    w.setSize();
    QTimer::singleShot(3000, &w,SLOT(showFullScreen()));
    return a.exec();
}
