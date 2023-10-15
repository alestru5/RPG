#include "hero.h"

Hero::Hero(QObject *parent): QObject(parent), QGraphicsItem(), experience(0), characteristic(0, 1, 1, 1, 2), max_health(100), current_health(100), position(0, 0){};

void Hero::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPolygon polygon;
    polygon << QPoint(-50, -50) << QPoint(50, -50) << QPoint(50, 50) << QPoint(-50, 50);
    painter->setBrush(Qt::red);
    painter->drawPolygon(polygon);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}



QRectF Hero::boundingRect() const {
    return QRectF(-50, 50, 50, 50);
}
