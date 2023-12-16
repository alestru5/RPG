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
            void resumeClicked();

    private slots:
        void onResumeClicked();
    private:
        QPushButton *resumeButton;
};

#endif // PAUSEMENU_H
