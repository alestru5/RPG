#include "pausemenu.h"

PauseMenu::PauseMenu(QWidget *parent): QWidget(parent) {
    resumeButton = new QPushButton(this);
    resumeButton->setText("Return");
    resumeButton->setObjectName(QString("returnButton"));
    resumeButton->setToolTip("Return");
    resumeButton->setGeometry(QRect(width/2 - 150, height / 2 , 300, 50));
    connect(resumeButton, SIGNAL(clicked()), this, SLOT(onResumeClicked()));

    quitButton = new QPushButton(this);
    quitButton->setText("Quit");
    quitButton->setObjectName(QString("quitButton"));
    quitButton->setToolTip("Quit program");
    quitButton->setGeometry(QRect(width/2 - 150, height / 2 + 100, 300, 50));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(onQuitClicked()));

    hide();
}

void PauseMenu::onResumeClicked(){
    emit resumeGame();
}
void PauseMenu::onQuitClicked(){
    hide();
    emit endGame();
}
void PauseMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width, height, QPixmap("/home/alestru/PetProjects/RPG/img/pause.png"));
    QWidget::paintEvent(event);
}

void PauseMenu::keyPressEvent(QKeyEvent *e){
    if (e->key() == Qt::Key_Escape){
        resumeGame();
    }
}


