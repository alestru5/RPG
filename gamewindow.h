#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtCore>
#include <QLabel>
#include <vector>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <iostream>

#include "cell.h"
class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QMainWindow *parent = nullptr);
    void keyPressEvent(QKeyEvent* e);
    void setSize();
private:
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    QPixmap wallPix;
    std::vector<QPixmap> playerPix;
    std::vector<std::vector<QLabel*>> tile;
    QPixmap nothingPix;
    const int tileHeight = 40;
    const int infoHeight = 80;
};

#endif // GAMEWINDOW_H
