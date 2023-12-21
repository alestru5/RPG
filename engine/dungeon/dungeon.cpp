#include "dungeon.h"
#include "../game.h"

Dungeon& Dungeon::initializeLevelsFile(std::ifstream &in, const json& config, Game &game){
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
                nlohmann::json jsonItem = config.at("items")[random() % config.at("items").size()];
                Item& c_pl = game.getPlugins().at(jsonItem["item_type"].get<std::string>());
                Item *I = c_pl.buildItem(jsonItem);
                Chest *c = new Chest(1, I);
                tmp.push_back(Cell(type_cell::floor, nullptr, c));
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
            else if (map[i][j] == 'O'){
                tmp.push_back(Cell(type_cell::open_door));
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
        nlohmann::json jsonItem = config.at("items")[random() % config.at("items").size()];
        Item& c_pl = game.getPlugins().at(jsonItem["item_type"].get<std::string>());
        Item *I = c_pl.buildItem(jsonItem);
        int x = std::stoi(map[i + 1]);
        int y = std::stoi(map[i + 2]);
        int lvl = std::stoi(map[i + 3]);
        if (map[i] == "wolf"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::blue_wolf, I)));
        } else if (map[i] == "tiger"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::red_tiger, I)));
        } else if (map[i] == "druid"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::black_druid, I)));
        } else if (map[i] == "golem"){
            enemies.push_back(std::make_pair(lvl, new Enemy(x, y, name_enemy::white_golem, I)));
        } else {
            throw std::invalid_argument("its not mob");
        }
    }
    return *this;
}

Dungeon &Dungeon::saveLevelsFile(std::ofstream &in, Game &game){
    in << count_levels<<std::endl;
    in << game.getMapWidth()<<std::endl;
    in << game.getMapHeight()<<std::endl;
    for (int i = 0; i < count_levels; i++){
        for (int x = 0; x < levels[i].getM(); x++){
            std::string tmp;
            for (int y = 0; y < levels[i].getN(); y++){
                if (hero.getX() == x && hero.getY() == y && i == cur_level){
                    tmp.append("H");
                } else if (levels[i][x][y].getType() == type_cell::wall){
                    tmp.append("#");
                } else if (levels[i][x][y].isChest()){
                    tmp.append("C");
                } else if (levels[i][x][y].getType() == type_cell::down_ladder){
                    tmp.append("D");
                } else if (levels[i][x][y].getType() == type_cell::up_ladder){
                    tmp.append("U");
                } else if (levels[i][x][y].getType() == type_cell::close_door){
                    tmp.append("E");
                } else if (levels[i][x][y].getType() == type_cell::open_door){
                    tmp.append("O");
                } else {
                    tmp.append("0");
                }

            }
            in << tmp<<std::endl;
        }
        in << "-"<<std::endl;
    }
    in << "Enemies:"<<std::endl;
    for (int i = 0; i < enemies.size(); i++){
        if (enemies[i].second->getName() == name_enemy::blue_wolf){
            in << "wolf"<<std::endl;
        } else if (enemies[i].second->getName() == name_enemy::red_tiger){
            in << "tiger"<<std::endl;
        } else if (enemies[i].second->getName() == name_enemy::black_druid){
            in << "druid"<<std::endl;
        } else if (enemies[i].second->getName() == name_enemy::white_golem){
            in << "golem"<<std::endl;
        }
        in << enemies[i].second->getX()<<std::endl;
        in << enemies[i].second->getY()<<std::endl;
        in << enemies[i].first<<std::endl;
    }
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
