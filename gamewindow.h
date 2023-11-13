#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMessageBox>
#include <QtCore>
#include <QLabel>
#include <vector>
#include <QKeyEvent>
#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QGraphicsView>
#include <iostream>
#include "game.h"


class GameWindow : public QMainWindow{
    Q_OBJECT

    private:
        Game game;

        QRect screenGeometry = QApplication::desktop()->screenGeometry();

        std::vector<QPixmap> playerPix;
        std::vector<std::vector<QLabel*>> tile;
        std::vector<std::vector<QLabel*>> hpTile;

        QPixmap wallPix;
        QPixmap nothingPix;
        QPixmap shadowPix;
        QPixmap chestPix;
        QPixmap ladderPix;
        QPixmap openDoorPix;
        QPixmap closeDoorPix;
        std::map<std::string, QPixmap> itemsPix;
        std::map<std::string, QPixmap> mobPix;
        QLabel* statusLabel;
        QLabel* statusBack;

        const int tileHeight = 40;
        const int infoHeight = 70;

        int timer;

    public:
        void setSize();

        explicit GameWindow(QMainWindow *parent = nullptr);

        void keyPressEvent(QKeyEvent* e);
        void timerEvent(QTimerEvent *e);

        void drawGame();
};

#endif // GAMEWINDOW_H
