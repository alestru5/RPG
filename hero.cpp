#include "hero.h"
#include "game.h"
#include "item.h"

Hero::Hero(): Character(), weapon(nullptr), table(), level(0), m_potion(5), c_bunch(30), potion(), equipment(), cur_endurance(100){}

Hero::Hero(int i, int j): Character(), weapon(nullptr), table(), level(0), m_potion(5), c_bunch(100), potion(), equipment(), cur_endurance(100){
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
    level = H.level;
    weapon = H.weapon;
    m_potion = H.m_potion;
    c_bunch = H.c_bunch;
}

Hero & Hero::setLevel(int l){
    if (l < 0){
        throw std::invalid_argument("negative level");
    }
    level = l;
    return *this;
}

Hero & Hero::setEquipment(std::list<Equipment*> &E){
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


Hero& Hero::operator = (const Hero &H){
    experience = H.experience;
    cur_endurance = H.cur_endurance;
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

void Hero::changeOrderPotion() noexcept{
    auto it = potion.end();
    auto it2 = potion.end();
    --it;
    --it2;
    potion.erase(it);
    potion.push_front(*it2);
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

std::string Hero::status(Dungeon &dungeon) const noexcept{
    std::string res;
    res += "HP: " + std::to_string(cur_hp) + "/" + std::to_string(max_hp);
    res += "\t\t\t\tDungeon Level: " + std::to_string(-dungeon.getCur_Level());
    res += "\t\t\t\tProtect: " + std::to_string(minProtect()) + "-" + std::to_string(maxProtect()) + "(+" + std::to_string(table.getValue(full_characteristic::strength) / 10) + ")";
    res += "\t\t\t\tFull damage: " + std::to_string(minDamage()) + "-" + std::to_string(maxDamage()) + "(+" + std::to_string(table.getValue(full_characteristic::agility    ) / 10) + ")";
    res += "\nLevel: " + std::to_string(level);
    res += "\tWeapon: ";
    if (weapon != nullptr){
        if (weapon->getItem_Type() == type_item::weapon_artifact){
            res += EnumToString::toString(dynamic_cast<WeaponArtifact *>(weapon)->getArtifact_Type()) + " ";
        }
        if (weapon->getItem_Type() == type_item::weapon_enchantment){
            res += EnumToString::toString(dynamic_cast<WeaponEnchantment *>(weapon)->getEnchantment_Type()) + " ";
        }
        if (weapon->getItem_Type() == type_item::weapon_artifact_enchantment){
            res += EnumToString::toString(dynamic_cast<WeaponArtifactEnchantment *>(weapon)->getArtifact_Type()) + " ";
            res += EnumToString::toString(dynamic_cast<WeaponArtifactEnchantment *>(weapon)->getEnchantment_Type()) + " ";
        }
        res += EnumToString::toString(weapon->getWeapon_Name());
    } else{
        res += "None";
    }
    res += "\tStrength: " + std::to_string(table.getValue(short_characteristic::s));
    res += "\tAgility: " + std::to_string(table.getValue(short_characteristic::a));
    res += "\tIntelligence: " + std::to_string(table.getValue(short_characteristic::i));
    res += "\tExperience: " + std::to_string(experience);
    res += "\tEndurance: " + std::to_string(cur_endurance) + "/" + std::to_string(table.getValue(short_characteristic::e));
    res += "\nHelmet: ";
    int f = 1;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::helmet){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Bib: ";
    f = 1;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::bib){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Leggings: ";
    f = 1;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::leggings){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "Boots: ";
    f = 1;
    for (auto iter = equipment.begin(); iter != equipment.end(); iter++){
        if ((*iter)->getEquipment_Type() == type_equipment::boots){
            if ((*iter)->getItem_Type() == type_item::equipment_artifact){
                res += EnumToString::toString(static_cast<EquipmentArtifact*>(*iter)->getArtifact_Type()) + " ";
            }
            res += EnumToString::toString((*iter)->getEquipment_Name(), (*iter)->getEquipment_Type()) + "\t";
            f = 0;
            break;
        }
    }
    if (f){
        res += "None\t";
    }

    res += "\nBunch: " + std::to_string(c_bunch);
    res += "\tPotion: ";
    if (potion.size() == 0){
        res += "None";
    }
    int c = 0;
    for (auto iter = potion.begin(); iter != potion.end(); iter++){
        res += EnumToString::toString((*iter)->getPotion_Name()) + " ";
        if (c + 2 == potion.size()) {
            res += "\t";
        }
        c += 1;
    }
    return res;
}

int Hero::act(std::string key, Dungeon &dungeon){
    std::string command = "invalid";
    if (key == "w") command = "north";
    else if (key == "s") command = "south";
    else if (key == "d") command = "east";
    else if (key == "a") command = "west";
    else if (key == "e") command = "action";
    else if (key == "f") command = "change";
    else if (key == "left") command = "attack";
    else if (key == "t") command = "drink";
    else if (key == "u") command = "strength";
    else if (key == "i") command = "intelligence";
    else if (key == "o") command = "agility";
    else if (key == "p") command = "endurance";
    if (command == "south" || command == "east" || command == "west" || command == "north"){
        type_destination destination;
        if (command == "south"){
            destination = type_destination::south;
        } else if (command == "east"){
            destination = type_destination::east;
        } else if (command == "west"){
            destination = type_destination::west;
        } else if (command == "north"){
            destination = type_destination::north;
        }
        move(destination, dungeon);
    } else if (command == "action"){
        if (climb(dungeon)){
            return 1;
        }
        if (open_chest(dungeon)){
            return 2;
        }
        if (take(dungeon)){
            updateHp();
            return 3;
        }
        if (change_door(dungeon)){
            return 4;
        }
        return 0;
    } else if (command == "attack"){
        int ind_enemy = findEnemy(dungeon);
        if (ind_enemy != -1){
            attack(dungeon.getEnemies()[ind_enemy].second);
            if (dungeon.getEnemies()[ind_enemy].second->isDead()){
                experience += dungeon.getEnemies()[ind_enemy].second->getExperience();
                dungeon.getEnemies()[ind_enemy].second->dropItem(dungeon);
                dungeon.enemyDead(ind_enemy);
            }
        }
    } else if (command == "change"){
        changeOrderPotion();
    } else if (command == "drink"){
        drinkPotion();
    } else if (command == "strength" || command == "intelligence" || command == "agility" || command == "endurance"){
        short_characteristic up;
        if (command == "strength") up = short_characteristic::s;
        if (command == "intelligence") up = short_characteristic::i;
        if (command == "agility") up = short_characteristic::a;
        if (command == "endurance") up = short_characteristic::e;
        levelUp(up);
    }
    updateHp();
    return 0;

}

void Hero::levelUp(short_characteristic n){
    if (experience < 200){
        return;
    }
    table.setValue(n, table.getValue(n) + 5);
    experience -= 200;
}

void Hero::drinkPotion(){
    if (potion.size()){
        auto it = potion.end();
        --it;
        (*it)->drink(*this);
        potion.pop_back();
    }
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
