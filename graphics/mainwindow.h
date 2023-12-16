#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsView>
#include <QMessageBox>





class Title;
class View;

class MainWindow : public QMainWindow{
    Q_OBJECT
    public slots:
        void closeWindow();
        void showWindow();
    public:
        MainWindow(QWidget *parent = nullptr);
        void setSize();

    private:
        QRect screenGeometry = QApplication::desktop()->screenGeometry();
        void createScene();

        Title *title;
        View *view;
};
#endif // MAINWINDOW_H
