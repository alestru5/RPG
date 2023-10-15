#ifndef HERO_H
#define HERO_H
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QKeyEvent>
#include <QGraphicsItem>
#include <QtCore>
#include <ncurses.h>

struct characteristic{
    int level;
    int strength;
    int agility;
    int intelligence;
    int endurance;
    characteristic(int l, int s, int a, int i, int e): level(l), strength(s), agility(a), intelligence(i), endurance(e){};
};

struct position{
    int x;
    int y;
    position(int x, int y): x(x), y(y){};
};

class Hero : public QObject, public QGraphicsItem
{
    Q_OBJECT
    private:
        int experience;
        struct characteristic characteristic;
        int max_health;
        int current_health;
        struct position position;
        /* оружие, список снаряжения, зелья*/

    public:
        explicit Hero(QObject *parent = 0);
        void slotGameTimer(QKeyEvent *e);
        struct position getPosition(){return position; }

    protected:
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        QRectF boundingRect() const;

};
#endif // HERO_H
