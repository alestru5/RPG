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
    private slots:
        void quitProgram();
        void startGame();

    private:
        int selection = 0;
        const int width = 1920;
        const int height = 1080;
        View *viewer;

        QPushButton *quitButton;
        QPushButton *startButton;

        GameWindow gamewindow;
};
#endif // TITLE_H
