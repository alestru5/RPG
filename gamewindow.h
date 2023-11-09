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
#include "hero.h"
#include "cell.h"

class GameWindow : public QMainWindow{
    Q_OBJECT

    private:
        QRect screenGeometry = QApplication::desktop()->screenGeometry();

        std::vector<QPixmap> playerPix;
        std::vector<std::vector<QLabel*>> tile;

        QPixmap wallPix;
        QPixmap nothingPix;
        QPixmap chestPix;
        QPixmap ladderPix;
        QPixmap openDoorPix;
        QPixmap closeDoorPix;
        std::map<std::string, QPixmap> itemsPix;
        QLabel* statusLabel;

        const int tileHeight = 40;
        const int infoHeight = 70;

    public:
        void setSize();
        explicit GameWindow(QMainWindow *parent = nullptr);
        void keyPressEvent(QKeyEvent* e);
};

#endif // GAMEWINDOW_H
