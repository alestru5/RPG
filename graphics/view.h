#ifndef VIEW_H
#define VIEW_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>

#include "mainwindow.h"

class View : public QGraphicsView{
    Q_OBJECT

    signals:
        void sceneChanged();

    public:
        View();
        void sceneSet(QGraphicsScene *);

};
#endif
