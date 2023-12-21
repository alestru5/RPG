#ifndef TITLE_H
#define TITLE_H

#include <QPushButton>

#include "mainwindow.h"
#include "gamewindow.h"

class View;

class Title : public QGraphicsScene{
    Q_OBJECT

    public:
        Title(View *view, QWidget *parent = 0);
    signals:
        void closeWindow();
        void showWindow();
    private slots:
        void quitProgram();
        void startGame();
        void startSelectGame(std::string in);
        void changesButton();
        void backToMenu();
        void quitGame();

    private:
        const int width = 1920;
        const int height = 1080;
        View *viewer;


        QPushButton *startButton;
        QPushButton *continueButton;
        QPushButton *quitButton;
        QPushButton *backButton;

        int count;
        QPushButton **mapsButton;

        GameWindow gamewindow;

        std::string pluginsDir = "/home/alestru/PetProjects/RPG/engine/item/plugins";
        std::ifstream lvl;
        std::ifstream config;
};
#endif // TITLE_H
