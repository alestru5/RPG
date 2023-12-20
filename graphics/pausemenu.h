#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsView>
#include <QObject>
#include <QLayout>
#include <QKeyEvent>

class PauseMenu: public QWidget {
    Q_OBJECT
    public:
        PauseMenu(QWidget *parent = nullptr);

        void paintEvent(QPaintEvent *event);
        void keyPressEvent(QKeyEvent* e);
    signals:
        void resumeGame();
        void endGame();
        void saveGame();

    private slots:
        void onResumeClicked();
        void onSaveClicked();
        void onQuitClicked();
    private:
        int width = 1920;
        int height = 1080;

        QPushButton *resumeButton;
        QPushButton *saveButton;
        QPushButton *quitButton;
};

#endif // PAUSEMENU_H
