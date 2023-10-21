#include "dungeon.h"

Dungeon::Dungeon(){
    levels = new Matrix<Cell>;
    std::ifstream in("/home/alestru/PetProjects/RPG/map.txt");
    std::vector<std::vector<Cell>> data;
    std::vector<std::string> map;
    std::string temp;

    while (in >> temp){
        map.push_back(temp);
    }

    for (int i = 0; i < map.size(); i++){
        std::vector<Cell> tmp;
        for (int j = 0; j < map[0].size(); j++){
            if (map[i][j] == '#'){
                tmp.push_back(Cell(type_cell::wall, i, j));
            } else if (map[i][j] == 'H'){
                tmp.push_back(Cell(type_cell::hero, i, j));
            }else{
                tmp.push_back(Cell(type_cell::floor, i, j));
            }
        }
        data.push_back(tmp);
    }
    levels[0] = Matrix<Cell>(data);
    in.close();
}
