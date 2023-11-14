#ifndef DUNGEON_H
#define DUNGEON_H

#include <vector>
#include<fstream>
#include <iostream>

#include "enemy.h"
#include "matrix.h"
#include "cell.h"
#include "hero.h"
#include "setitem.h"

class Game;

class Dungeon{
    private:
        int count_levels;
        int cur_level;
        Hero hero;
        std::vector<std::pair<int, Enemy *>> enemies;
        Matrix<Cell>* levels;

    public:
        Dungeon(): count_levels(0), cur_level(0), hero(), levels(nullptr) {}
        ~Dungeon();

        Dungeon& initializeLevelsFile(std::ifstream &in, Game &game);
        Dungeon& initializeEnemiesFile(std::ifstream &in, Game &game);

        int getCount_Levels() const noexcept {return count_levels; }
        int getCur_Level() const noexcept { return cur_level; }
        Matrix<Cell>* getLevels() const noexcept {return levels;}
        Hero &getHero() noexcept { return hero; }
        Matrix<Cell>& getCurLevel() noexcept { return levels[cur_level]; }
        std::vector<std::pair<int, Enemy *>> getEnemies() const noexcept { return enemies; }

        Dungeon &up_level() {cur_level+= 1; return *this; }
        Dungeon &down_level() {cur_level-= 1; return *this; }

        void enemyDead(int ind_enemy);

        Dungeon& move_door(int i, int j);

};

#endif // DUNGEON_H
