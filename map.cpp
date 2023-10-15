#include "map.h"
#include "ui_map.h"

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    m_hero();
    connect(&m_timer, &QTimer::timeout, this, &Map::moveHero);
}

Map::~Map()
{
    delete ui;
}
