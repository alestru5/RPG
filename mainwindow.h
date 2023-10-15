#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QDebug>
#include "gamewindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsView>
#include "view.h"
#include "title.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Title;
class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void setSize();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    GameWindow gamewindow;
    QRect screenGeometry = QApplication::desktop()->screenGeometry();
    void createScene();
    enum { maxState = 10 };
    Title *title;
    View *view;


};
#endif // MAINWINDOW_H
