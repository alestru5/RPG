#ifndef TITLE_H
#define TITLE_H

#include <QPushButton>

#include "mainwindow.h"
/*#include "myscene.h"*/



class View;
/*class AnimatedGraphicsItem : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
};*/

class Title : public QGraphicsScene{
    Q_OBJECT
public:
    Title(View *view, QWidget *parent = 0);

signals:
    /*void quitGame();*/

protected:


private slots:
    void quitProgram();
    void startGame();

private:
    int selection = 0;
    const int width = 1280;
    const int height = 720;
    /*AnimatedGraphicsItem *background;*/
    View *viewer;
    /*QGraphicsPixmapItem *foreground;
    QGraphicsPixmapItem *logo;*/
    QGraphicsTextItem *quit;
    /*QPropertyAnimation *animation;*/
    QPushButton *quitButton;
    QPushButton *startButton;
};
#endif // TITLE_H
