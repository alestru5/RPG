#include "hero.h"
#include "game.h"

Hero::Hero(): Character(), weapon(nullptr), table(), level(0), m_potion(5), c_bunch(100), potion(), equipment(){}
Hero::Hero(int i, int j): Character(), weapon(nullptr), table(), level(0), m_potion(5), c_bunch(100), potion(), equipment(){
    x = i;
    y = j;
}

Hero::Hero(const Hero &H){
    experience = H.experience;
    max_hp = H.max_hp;
    cur_hp = H.cur_hp;
    x = H.x;
    y = H.y;
    level = H.level;
    weapon = H.weapon;
    m_potion = H.m_potion;
    c_bunch = H.c_bunch;
}

int Hero::act(std::string key){
    std::string command = "invalid";
    if (key == "w") command = "north";
    else if (key == "s") command = "south";
    else if (key == "d") command = "east";
    else if (key == "a") command = "west";
    else if (key == "e") command = "take";
    else if (key == "f") command = "open";
    if (command == "south" || command == "east" || command == "west" || command == "north"){
        if(move(command)){
            return 1;
        }
    } else if (command == "open"){
        if (open()){
            return 1;
        }
        return 0;
    }
    return 0;

}





Hero & Hero::setLevel(int l){
    if (l < 0){
        throw std::invalid_argument("negative level");
    }
    level = l;
    return *this;
}

Hero & Hero::setEquipment(std::list<Equipment> &E){
    equipment = E;
    return *this;
}

Hero & Hero::setM_Potion(int m){
    if (m < 0){
        throw std::invalid_argument("error count");
    }
    m_potion = m;
    return *this;
}

Hero & Hero::setC_Bunch(int b){
    if (b < 0){
        throw std::invalid_argument("negative bunch");
    }
    c_bunch = b;
    return *this;
}

bool Hero::move(std::string direction){
    Cell destination;
    int i2 = x, j2 = y;
    if (direction == "south"){
        destination = Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][x + 1][y];
        i2 += 1;
    } else if (direction == "east"){
        destination = Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][x][y + 1];
        j2 += 1;
    } else if (direction == "west"){
        destination = Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][x][y -1];
        j2 -= 1;
    } else if (direction == "north"){
        destination = Game::dungeon.getLevels()[Game::dungeon.getCur_Level()][x-1][y];
        i2 -= 1;
    } else{
        return false;
    }

    if (destination.getType() == type_cell::floor && destination.getChest() == nullptr && destination.getItem() == nullptr){
        x = i2;
        y = j2;
        return true;
    }
    return false;
}

Hero& Hero::operator = (const Hero &H){
    experience = H.experience;
    max_hp = H.max_hp;
    cur_hp = H.cur_hp;
    x = H.x;
    y = H.y;
    level = H.level;
    weapon = H.weapon;
    m_potion = H.m_potion;
    c_bunch = H.c_bunch;
    return *this;
}

std::string Hero::status() const noexcept{
    std::string res;
    res += "HP: " + std::to_string(max_hp) + "/" + std::to_string(cur_hp);
    res += "\nLevel: " + std::to_string(level);
    if (weapon != nullptr){
        res += "\tWeapon: " + EnumToString::toString(weapon->getWeapon_Name());
    } else{
        res += "\tWeapon: None";
    }
    res += "\nEquipment: ";
    if (equipment.size() == 0){
        res += "None";
    }
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        res += EnumToString::toString((*iter).getEquipment_Name(), (*iter).getEquipment_Type()) + " ";
    }
    res += "\nBunch: " + std::to_string(c_bunch);
    res += "\tPotion: ";
    if (potion.size() == 0){
        res += "None";
    }
    for (auto iter = potion.begin(); iter != potion.end(); iter++){
        res += EnumToString::toString((*iter).getPotion_Name());
    }
    return res;
}

bool Hero::open() noexcept{
    if (Game::dungeon.getCurLevel()[x][y+1].isChest()){
        std::pair<bool, bool> check = Game::dungeon.getCurLevel()[x][y+1].getChest()->tryToOpen();
        if (check.first){
            Game::dungeon.getCurLevel()[x][y+1].setItem(Game::dungeon.getCurLevel()[x][y+1].getChest()->getItem());
            Game::dungeon.getCurLevel()[x][y+1].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (Game::dungeon.getCurLevel()[x][y-1].isChest()){
        std::pair<bool, bool> check = Game::dungeon.getCurLevel()[x][y-1].getChest()->tryToOpen();
        if (check.first){
            Game::dungeon.getCurLevel()[x][y-1].setItem(Game::dungeon.getCurLevel()[x][y-1].getChest()->getItem());
            Game::dungeon.getCurLevel()[x][y-1].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (Game::dungeon.getCurLevel()[x+1][y].isChest()){
        std::pair<bool, bool> check = Game::dungeon.getCurLevel()[x+1][y].getChest()->tryToOpen();
        if (check.first){
            Game::dungeon.getCurLevel()[x+1][y].setItem(Game::dungeon.getCurLevel()[x+1][y].getChest()->getItem());
            Game::dungeon.getCurLevel()[x+1][y].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (Game::dungeon.getCurLevel()[x-1][y].isChest()){
        std::pair<bool, bool> check = Game::dungeon.getCurLevel()[x-1][y].getChest()->tryToOpen();
        if (check.first){
            Game::dungeon.getCurLevel()[x-1][y].setItem(Game::dungeon.getCurLevel()[x-1][y].getChest()->getItem());
            Game::dungeon.getCurLevel()[x-1][y].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }
    return false;
}
