#include "pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent): QWidget(parent) {
    this->setStyleSheet("background-image: url(/home/alestru/PetProjects/RPG/img/menu2.png);");

    resumeButton = new QPushButton("Resume", this);

    hide();
    connect(resumeButton, &QPushButton::clicked, this, &PauseMenu::resumeClicked);
}

void PauseMenu::onResumeClicked(){
    emit resumeClicked();
    hide();
}

void PauseMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), QPixmap("/home/alestru/PetProjects/RPG/img/menu2.png"));
    // рисует изображение вверху
    QWidget::paintEvent(event);
}

void PauseMenu::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Escape){
        if (!isVisible()) {
            showFullScreen();
            emit resumeClicked();
        } else {
            hide();
            emit resumeClicked();
        }
    }
}
