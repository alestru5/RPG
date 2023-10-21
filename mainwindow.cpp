#include "mainwindow.h"
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent){
    createScene();
    setCentralWidget(view);
    setWindowTitle("Vagabund");
}



void MainWindow::setSize(){

    this->setFixedSize(1280,720);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

void MainWindow::createScene(){
    view = new View;
    title = new Title(view);
}

