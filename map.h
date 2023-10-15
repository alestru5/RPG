#ifndef MAP_H
#define MAP_H

#include <QWidget>

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();
private slots:
    void moveHero();
private:
    Ui::Map *ui;
    QTimer m_timer;
    Hero* m_hero;
};

#endif // MAP_H
