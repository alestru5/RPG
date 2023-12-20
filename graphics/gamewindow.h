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



#include "../engine/game.h"
#include "../engine/helps/enums.h"
#include "pausemenu.h"

class GameWindow : public QMainWindow{
    Q_OBJECT
    signals:
        void quitGame();
    private slots:
        void pause();
        void endGame();
        void saveGame();
    private:
        Game game;

        PauseMenu *pauseMenu;
        QRect screenGeometry = QApplication::desktop()->screenGeometry();

        std::vector<QPixmap> playerPix;
        std::vector<std::vector<QLabel*>> tile;
        std::vector<std::vector<QLabel*>> hpTile;

        QPixmap avatar;
        QPixmap nothingPix;
        QPixmap shadowPix;
        QPixmap chestPix;
        QPixmap potionPix;
        QPixmap bunchPix;

        std::map<std::string, QPixmap> weaponPix;
        std::map<std::string, QPixmap> equipmentPix;
        std::map<type_cell, QPixmap> cellPix;
        std::map<name_enemy, QPixmap> mobPix;
        std::map<std::string, QPixmap> characteristicPix;

        QLabel* info;


        std::vector<std::vector<QLabel*>> characteristicSlots;
        QLabel *bunchSlot;
        QLabel *bunchCount;
        QLabel *weaponSlot;
        std::vector<std::vector<QLabel*>> equipmentSlot;
        std::vector<std::vector<QLabel*>> inventorySlot;
        QGraphicsView* bar;
        QGraphicsRectItem * hpBar;
        QGraphicsRectItem * eBar;

        const int tileHeight = 60;
        const int infoHeight = 120;

        int timer;

    public:
        void setSize();

        explicit GameWindow(QMainWindow *parent = nullptr);

        Game& getGame() noexcept { return game; }

        void loadImg();
        void drawTools();
        void drawInventory();
        void drawMob();

        void startTick() { timer = startTimer(1000); }
        void stopTick() { killTimer(timer); }

        void start(std::ifstream &in, const json& config);

        void mousePressEvent(QMouseEvent *e);
        void wheelEvent(QWheelEvent* event);
        void keyPressEvent(QKeyEvent* e);
        void timerEvent(QTimerEvent *e);
        void drawGame();
        void act(std::string key);

};

#endif // GAMEWINDOW_H
