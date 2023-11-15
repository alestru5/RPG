#include "hero.h"
#include "game.h"
#include "item.h"

Hero::Hero(): Character(), weapon(nullptr), table(), c_bunch(30), curr_chosen_item(0), cur_endurance(100), inventory(m_inventory * 10, nullptr){}

Hero::Hero(int i, int j): Character(), weapon(nullptr), table(), curr_chosen_item(0), c_bunch(100), cur_endurance(100), inventory(m_inventory * 10, nullptr){
    x = i;
    y = j;
}

Hero::Hero(const Hero &H){
    experience = H.experience;
    cur_endurance = H.cur_endurance;
    max_hp = H.max_hp;
    cur_hp = H.cur_hp;
    x = H.x;
    y = H.y;
    weapon = H.weapon;
    curr_chosen_item = H.curr_chosen_item;
    inventory = H.inventory;
    c_bunch = H.c_bunch;
}

Hero & Hero::setLevel(int l){
    if (l < 0){
        throw std::invalid_argument("negative level");
    }
    return *this;
}

Hero & Hero::setEquipment(std::list<Equipment*> &E){
    equipment = E;
    return *this;
}

Hero &Hero::setCurr_Chosen_Item(int a){
    if (a <= 0){
        throw std::invalid_argument("not positive position");
    }
    if (a > m_inventory){
        throw std::invalid_argument("position out of range");
    }
    curr_chosen_item = a;
    return *this;
}

Hero & Hero::setC_Bunch(int b){
    if (b < 0){
        throw std::invalid_argument("negative bunch");
    }
    c_bunch = b;
    return *this;
}

Hero &Hero::setCur_Endurance(int a){
    if (a <= 0){
        throw std::invalid_argument("not positive endurace");
    }
    cur_endurance = a;
    return *this;
}


Hero& Hero::operator = (const Hero &H){
    experience = H.experience;
    cur_endurance = H.cur_endurance;
    max_hp = H.max_hp;
    cur_hp = H.cur_hp;
    x = H.x;
    y = H.y;
    weapon = H.weapon;
    c_bunch = H.c_bunch;
    inventory = H.inventory;
    return *this;
}

int Hero::fullProtect() const noexcept{
    int protect = 0;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        protect += (*iter)->getProtect();
    }
    return protect;
}

int Hero::minProtect() const noexcept{
    int protect = 0;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        protect += (*iter)->getMin_Protect();
    }
    return protect;
}

int Hero::maxProtect() const noexcept{
    int protect = 0;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        protect += (*iter)->getMax_Protect();
    }
    return protect;
}

int Hero::minDamage() const noexcept{
    if (weapon){
        return weapon->getMin_Damage();
    }
    return 0;
}

int Hero::maxDamage() const noexcept{
    if (weapon){
        return weapon->getMax_Damage();
    }
    return 0;
}

void Hero::getDamage(int damage){
    int protect = table.getValue(full_characteristic::strength) / 10 + fullProtect();
    if (rand() % 100 >= (table.getValue(full_characteristic::endurance) - 50) / 100){
        cur_hp -= std::max((damage - protect), 1);
    }
}

int Hero::findEnemy(Dungeon &dungeon) const noexcept{
    std::vector<std::pair<int, Enemy *>> tmp= dungeon.getEnemies();
    for (size_t i = 0; i < tmp.size(); i++){
        if (tmp[i].first == dungeon.getCur_Level()){
            if (tmp[i].second->getX() == x && abs(tmp[i].second->getY() - y) == 1 ||
                tmp[i].second->getY() == y && abs(tmp[i].second->getX() - x) == 1){
                return i;
            }
        }
    }
    return -1;
}

int Hero::fullDamage(Enemy *enemy) const noexcept{
    if (weapon){
        return weapon->getDamage(enemy) + table.getValue(full_characteristic::agility) / 10;
    }else{
        return table.getValue(full_characteristic::agility) / 10;
    }
}

void Hero::updateEndurance() noexcept{
    cur_endurance = std::min(cur_endurance + 20, table.getValue(short_characteristic::e));

}

void Hero::updateHp() noexcept{
    double coef = static_cast<double>(cur_hp) / static_cast<double>(max_hp);
    max_hp = table.getValue(short_characteristic::s) * 2;
    cur_hp = static_cast<int>(coef * max_hp);
}

void Hero::addExperience(int a){
    if (a < 0){
        throw std::invalid_argument("negative experince");
    }
    experience += a;
}

void Hero::levelUp(short_characteristic n){
    if (experience < 200){
        return;
    }
    table.setValue(n, table.getValue(n) + 5);
    experience -= 200;
}

void Hero::attack(Character *C){
    if (!C->isDead()){
        int damage = fullDamage(static_cast<Enemy *>(C));
        static_cast<Enemy *>(C)->getDamage(damage);
    }

}

bool Hero::take(Dungeon &dungeon){
    if (dungeon.getCurLevel()[x][y+1].isItem()){
        dungeon.getCurLevel()[x][y+1].setItem(dungeon.getCurLevel()[x][y+1].getItem()->take(this));
        return true;
    }
    else if (dungeon.getCurLevel()[x][y-1].isItem()){
        dungeon.getCurLevel()[x][y-1].setItem(dungeon.getCurLevel()[x][y-1].getItem()->take(this));
        return true;
    }
    else if (dungeon.getCurLevel()[x+1][y].isItem()){
        dungeon.getCurLevel()[x+1][y].setItem(dungeon.getCurLevel()[x+1][y].getItem()->take(this));
        return true;
    }
    else if (dungeon.getCurLevel()[x-1][y].isItem()){
        dungeon.getCurLevel()[x-1][y].setItem(dungeon.getCurLevel()[x-1][y].getItem()->take(this));
        return true;
    }
    return false;
}

void Hero::move(type_destination direction, Dungeon &dungeon){
    if (cur_endurance <= 0){
        return;
    }
    Cell destination;
    int i2 = x, j2 = y;
    if (direction == type_destination::south){
        destination = dungeon.getCurLevel()[x + 1][y];
        i2 += 1;
    } else if (direction == type_destination::east){
        destination = dungeon.getCurLevel()[x][y + 1];
        j2 += 1;
    } else if (direction == type_destination::west){
        destination = dungeon.getCurLevel()[x][y - 1];
        j2 -= 1;
    } else if (direction == type_destination::north){
        destination = dungeon.getCurLevel()[x - 1][y];
        i2 -= 1;
    }

    if ((destination.getType() == type_cell::floor || destination.isLadder() || destination.isOpenDoor()) && destination.getChest() == nullptr && destination.getItem() == nullptr){
        x = i2;
        y = j2;
        cur_endurance -= 5;
    }
}

bool Hero::open_chest(Dungeon &dungeon) noexcept{
    if (c_bunch <= 0){
        return false;
    }
    if (dungeon.getCurLevel()[x][y+1].isChest()){
        std::pair<bool, bool> check = dungeon.getCurLevel()[x][y+1].getChest()->tryToOpen(this);
        if (check.first){
            dungeon.getCurLevel()[x][y+1].setItem(dungeon.getCurLevel()[x][y+1].getChest()->getItem());
            dungeon.getCurLevel()[x][y+1].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (dungeon.getCurLevel()[x][y-1].isChest()){
        std::pair<bool, bool> check = dungeon.getCurLevel()[x][y-1].getChest()->tryToOpen(this);
        if (check.first){
            dungeon.getCurLevel()[x][y-1].setItem(dungeon.getCurLevel()[x][y-1].getChest()->getItem());
            dungeon.getCurLevel()[x][y-1].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (dungeon.getCurLevel()[x+1][y].isChest()){
        std::pair<bool, bool> check = dungeon.getCurLevel()[x+1][y].getChest()->tryToOpen(this);
        if (check.first){
            dungeon.getCurLevel()[x+1][y].setItem(dungeon.getCurLevel()[x+1][y].getChest()->getItem());
            dungeon.getCurLevel()[x+1][y].setChest(nullptr);
            c_bunch -= 1;
            return true;
        }
        if (check.second){
            c_bunch -= 1;
        }
        return false;
    }

    if (dungeon.getCurLevel()[x-1][y].isChest()){
        std::pair<bool, bool> check = dungeon.getCurLevel()[x-1][y].getChest()->tryToOpen(this);
        if (check.first){
            dungeon.getCurLevel()[x-1][y].setItem(dungeon.getCurLevel()[x-1][y].getChest()->getItem());
            dungeon.getCurLevel()[x-1][y].setChest(nullptr);
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

bool Hero::climb(Dungeon &dungeon) noexcept{
    if (dungeon.getCurLevel()[x][y].isLadder()){
        if (dungeon.getCurLevel()[x][y].getType() == type_cell::down_ladder
            && dungeon.getLevels()[dungeon.getCur_Level() + 1][x][y].getType() == type_cell::up_ladder){
            if (dungeon.getCur_Level() != dungeon.getCount_Levels() - 1){
                dungeon.up_level();
                return true;
            }
            return false;
        }
        if (dungeon.getCurLevel()[x][y].getType() == type_cell::up_ladder
            && dungeon.getLevels()[dungeon.getCur_Level() - 1][x][y].getType() == type_cell::down_ladder){
            if (dungeon.getCur_Level() != 0){
                dungeon.down_level();
                return true;
            }
            return false;
        }
    }


    return false;
}

bool Hero::change_door(Dungeon &dungeon) noexcept {
    if (dungeon.getCurLevel()[x][y+1].isDoor()){
        Cell tmp = dungeon.getCurLevel()[x][y+1];
        tmp.changeDoor();
        dungeon.getCurLevel().setValue(x, y+1, tmp);
       return true;
    } else if (dungeon.getCurLevel()[x][y-1].isDoor()){
       Cell tmp = dungeon.getCurLevel()[x][y-1];
       tmp.changeDoor();
       dungeon.getCurLevel().setValue(x, y-1, tmp);
       return true;
    } else if (dungeon.getCurLevel()[x+1][y].isDoor()){
       Cell tmp = dungeon.getCurLevel()[x+1][y];
       tmp.changeDoor();
       dungeon.getCurLevel().setValue(x+1, y, tmp);
       return true;
    } else if (dungeon.getCurLevel()[x-1][y].isDoor()){
       dungeon.getCurLevel()[x-1][y].changeDoor();
       return true;
    }
    return false;
}
