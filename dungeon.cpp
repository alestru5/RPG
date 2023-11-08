#include "dungeon.h"
#include "hero.h"
#include "enumtostring.h"
Dungeon& Dungeon::initializeLevelsFile(){
    std::ifstream in("/home/alestru/PetProjects/RPG/map.txt");
    std::vector<std::vector<Cell>> data;
    std::vector<std::string> map;
    std::string temp;
    in >> count_levels;
    cur_level = 0;
    levels = new Matrix<Cell>[count_levels];
    while (in >> temp){
        map.push_back(temp);
    }
    for (size_t i = 0; i < map.size(); i++){
        std::vector<Cell> tmp;
        for (size_t j = 0; j < map[0].size(); j++){

            if (map[i][j] == '#'){
                tmp.push_back(Cell(type_cell::wall));

            } else if (map[i][j] == 'H'){
                tmp.push_back(Cell(type_cell::floor));
                hero.setX(i);
                hero.setY(j);
            } else if (map[i][j] == 'C'){
                Item *t = nullptr;
                Item *I = SetItem::createItem();
                Chest *c = new Chest(1, I);
                tmp.push_back(Cell(type_cell::floor, t, c));
            }
            else{
                tmp.push_back(Cell(type_cell::floor));
            }
        }
        data.push_back(tmp);
    }
    levels[0] = Matrix<Cell>(data);
    in.close();
}


Dungeon& Dungeon::move_door(int i, int j){
    if (i < 0 || j < 0 || i >= levels[count_levels-1].getM() || j >= levels[count_levels-1].getN()){
        throw std::invalid_argument("index error");
    }
    if (levels[count_levels-1][i][j].getType() != type_cell::close_door ||
        levels[count_levels-1][i][j].getType() != type_cell::open_door){
        throw std::invalid_argument("its not door");
    }
    if (levels[count_levels-1][i][j].getType() == type_cell::close_door){
        levels[count_levels-1][i][j].setType(type_cell::open_door);
    } else{
        levels[count_levels-1][i][j].setType(type_cell::close_door);
    }
}

Dungeon::~Dungeon(){
    for (int i = 0; i < count_levels; i++){
        levels[i].~Matrix();
    }
    delete [] enemies;
}
