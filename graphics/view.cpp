#include "view.h"

View::View() {
    this->setFixedSize(QSize(1920, 1080));
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::sceneSet(QGraphicsScene *scene) {
    QPixmap backgroundImage("/home/alestru/PetProjects/RPG/img/menu2.png");
    QSize PicSize(1920, 1080);
    this->setFrameShape(QFrame::NoFrame);

    backgroundImage = backgroundImage.scaled(PicSize,Qt::KeepAspectRatio);
    QBrush backgroundBrush(backgroundImage);
    this->setBackgroundBrush(backgroundBrush);

    setScene(scene);
    emit sceneChanged();
}
