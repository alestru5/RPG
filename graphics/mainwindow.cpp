#include "mainwindow.h"
#include "title.h"
#include "view.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent){
    createScene();
    setCentralWidget(view);
    setWindowTitle("Vagabund");
    connect(title, &Title::closeWindow, this, &MainWindow::closeWindow);
}

void MainWindow::closeWindow(){
    this->close();
}

void MainWindow::setSize(){
    this->setFixedSize(1920,1080);
    int x = ((screenGeometry.width() - this->width()) / 2);
    int y = ((screenGeometry.height() - this->height()) / 2);
    this->move(x, y);
}

void MainWindow::createScene(){
    view = new View;
    title = new Title(view);
}

