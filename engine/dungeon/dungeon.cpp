#include "dungeon.h"
#include "../character/hero/hero.h"
#include "../game.h"
#include "../helps/enumtostring.h"

Dungeon& Dungeon::initializeLevelsFile(std::ifstream &in, Game &game){
    std::vector<std::string> map;
    std::string temp;
    in >> count_levels;
    int a;
    int index;
    in >> a;
    game.setMapWidth(a);
    in >> a;
    game.setMapHeight(a);
    cur_level = 0;
    levels = new Matrix<Cell>[count_levels];
    while (in >> temp){
        map.push_back(temp);
    }
    int l = 0;
    std::vector<std::vector<Cell>> data;
    for (size_t i = 0; i < map.size(); i++){
        std::vector<Cell> tmp;
        if (map[i] == "Enemies:"){
            index = i + 1;
            break;
        }
        for (size_t j = 0; j < map[i].size(); j++){
            if (map[i][j] == '-'){
                if (data.size() != game.getMapHeight()){
                    throw std::runtime_error("Error of size map");
                }
                if(l == 0 && hero.getX() == -1){
                    throw std::runtime_error("No hero");
                }
                Matrix<Cell> m_tmp(data);
                levels[l] = m_tmp;
                std::vector<Cell> t;
                for (int u = 0 ; u < levels[l].getM(); u++){
                    for(int p = 0; p < levels[l].getN(); p++){
                        t.push_back(levels[l][u][p]);
                    }

                }
                l += 1;

                data.erase(data.begin(), data.end());
                break;
            }
            if (map[i][j] == '#'){
                tmp.push_back(Cell(type_cell::wall));

            }
            else if (l == 0 && map[i][j] == 'H'){
                tmp.push_back(Cell(type_cell::floor));
                hero.setX(i);
                hero.setY(j);
            }
            else if(l != 0 && map[i][j] == 'H'){
                throw std::runtime_error("Hero can be only on first level");
            }
            else if (map[i][j] == 'C'){
                Item *t = nullptr;
                Item *I = SetItem::createItem();
                Chest *c = new Chest(1, I);
                tmp.push_back(Cell(type_cell::floor, t, c));
            }
            else if (map[i][j] == 'D'){
                tmp.push_back(Cell(type_cell::down_ladder));
            }
            else if (map[i][j] == 'U'){
                tmp.push_back(Cell(type_cell::up_ladder));
            }
            else if (map[i][j] == 'E'){
                tmp.push_back(Cell(type_cell::close_door));
            }
            else{
                tmp.push_back(Cell(type_cell::floor));
            }
        }
        if (map[i][0] != '-'){
            if (tmp.size() != game.getMapWidth()){
                throw std::runtime_error("Error of size map");
            }
            data.push_back(tmp);
        }
    }
    if (l != count_levels){
        throw std::runtime_error("Error of count levels");
    }
    enemies.clear();
    for (int i = index; i < map.size(); i+= 4){
        int x = std::stoi(map[i + 1]);
        int y = std::stoi(map[i + 2]);
        int lvl = std::stoi(map[i + 3]);
        if (map[i] == "wolf"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::blue_wolf)));
        } else if (map[i] == "tiger"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::red_tiger)));
        } else if (map[i] == "druid"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::black_druid)));
        } else if (map[i] == "golem"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::white_golem)));
        } else {
            throw std::invalid_argument("its not mob");
        }
    }
    return *this;
}

void Dungeon::enemyDead(int ind_enemy){
    if (ind_enemy > enemies.size()){
        throw std::invalid_argument("index out of range");
    }
    enemies.erase(enemies.begin() + ind_enemy);
}

Dungeon& Dungeon::move_door(int i, int j){
    if (i < 0 || j < 0 || i >= levels[cur_level].getM() || j >= levels[cur_level].getN()){
        throw std::invalid_argument("index error");
    }
    if (levels[cur_level][i][j].getType() != type_cell::close_door &&
        levels[cur_level][i][j].getType() != type_cell::open_door){
        throw std::invalid_argument("its not door");
    }
    levels[cur_level][i][j].changeDoor();
    return *this;
}

Dungeon::~Dungeon(){
    for (int i = 0; i < count_levels; i++){
        levels[i].~Matrix();
    }
}
