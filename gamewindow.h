#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QtCore>
#include <QKeyEvent>

#include "hero.h"

namespace Ui {
class GameWindow;
}

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
protected:
private:
    Ui::GameWindow *ui;
    QGraphicsScene *scene;
    Hero *hero;
    QTimer *timer;
};

#endif // GAMEWINDOW_H
