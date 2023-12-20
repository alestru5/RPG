#include "enemy.h"
#include "../../helps/sets/setitem.h"
#include "../../game.h"

Enemy::Enemy() noexcept: experience(100), Character(), name(name_enemy::white_golem){
    experience = 100;
    min_damage = SetDamage::createDamage(name_enemy::white_golem).first;
    max_damage = SetDamage::createDamage(name_enemy::white_golem).second;
    /*item = SetItem::createItem();*/
    item = nullptr;
}
Enemy::Enemy(int i, int j) noexcept: Enemy(){
    experience = 100;
    x = i;
    y = j;
}

Enemy::Enemy(int i, int j, name_enemy n) noexcept: experience(100), Character(), name(n){
    experience = 100;
    min_damage = SetDamage::createDamage(n).first;
    max_damage = SetDamage::createDamage(n).second;
    /*item = SetItem::createItem();*/
    item = nullptr;
    x = i;
    y = j;
}

bool Enemy::isNear(Dungeon &dungeon) const noexcept{
    int hx = dungeon.getHero().getX();
    int hy = dungeon.getHero().getY();
    if ((x == hx && (abs(hy - y) == 1)) ||
        (y == hy && abs(hx - x) == 1)){
        return true;
    }
    return false;
}

type_destination Enemy::vision(Dungeon &dungeon) const noexcept{
    int hx = dungeon.getHero().getX();
    int hy = dungeon.getHero().getY();
    if (abs(hx - x) >= 5 || abs(hy - y) >= 5 || isNear(dungeon)){
        return type_destination::none;
    }
    int prev_j = std::min(static_cast<int>(y), hy);
    for (int i = std::min(static_cast<int>(x), hx); i < std::max(static_cast<int>(x), hx) + 1; i++){
        double j;
        int u_j;
        if (hx + 1 - x != 0){
            j = static_cast <double> ((i - x) * (hy + 1 - y) / (hx + 1 - x)) + static_cast<double> (y);
        } else{
            j = hy + 1;

        }
        u_j = std::floor(j);

        for (int k = prev_j; k < u_j; k++){
            if (dungeon.getCurLevel()[i][k].isWall() || dungeon.getCurLevel()[i][k].getType() == type_cell::close_door ||
                dungeon.getCurLevel()[i][k].getItem() != nullptr || dungeon.getCurLevel()[i][k].isChest()){
                return type_destination::none;
            }
        }
        prev_j = u_j;
    }

    Cell destination = dungeon.getCurLevel()[x-1][y];
    if (x > hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::north;
    }
    destination = dungeon.getCurLevel()[x+1][y];
    if (x < hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::south;
    }
    destination = dungeon.getCurLevel()[x][y+1];
    if (y < hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::east;
    }
    destination = dungeon.getCurLevel()[x][y-1];
    if (y > hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::west;
    }
    return type_destination::none;
}

bool Enemy::findEnemy(Dungeon &dungeon, int i, int j){
    for (size_t k = 0; k < dungeon.getEnemies().size(); k++){
        if (dungeon.getEnemies()[k].first == dungeon.getCur_Level() && dungeon.getEnemies()[k].second->getX() == i && dungeon.getEnemies()[k].second->getY() == j){
            return true;
        }
    }
    return false;
}
void Enemy::move(type_destination direction, Dungeon &dungeon) noexcept{
    if (isDead()){
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

    dungeon.getCurLevel()[i2][j2].getBusy().acquire();
    if (!findEnemy(dungeon, i2, j2) && (destination.getType() == type_cell::floor || destination.isLadder() || destination.isOpenDoor()) && destination.getChest() == nullptr && destination.getItem() == nullptr){
        x = i2;
        y = j2;
    }
    dungeon.getCurLevel()[i2][j2].getBusy().release();
}

void Enemy::randomMoveMob(Dungeon &dungeon) noexcept{
    if (isDead()){
        return;
    }

    int a = rand() % 4;
    Cell destination;
    destination = dungeon.getCurLevel()[x-1][y];
    dungeon.getCurLevel()[x-1][y].getBusy().acquire();
    if (!findEnemy(dungeon, x - 1, y) && a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() || destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   dungeon.getCurLevel()[x-1][y].getItem() == nullptr)){
        x -= 1;
        dungeon.getCurLevel()[x][y].getBusy().release();
        return;
    }

    dungeon.getCurLevel()[x-1][y].getBusy().release();
    a = rand() % 3;
    dungeon.getCurLevel()[x+1][y].getBusy().acquire();
    destination = dungeon.getCurLevel()[x+1][y];
    if (!findEnemy(dungeon, x - 1, y) && a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        x += 1;
        dungeon.getCurLevel()[x][y].getBusy().release();
        return;
    }

    a = rand() % 2;
    dungeon.getCurLevel()[x+1][y].getBusy().release();
    dungeon.getCurLevel()[x][y+1].getBusy().acquire();
    destination = dungeon.getCurLevel()[x][y+1];
    if (!findEnemy(dungeon, x - 1, y) && a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        y += 1;
        dungeon.getCurLevel()[x][y].getBusy().release();
        return;
    }

    dungeon.getCurLevel()[x][y+1].getBusy().release();
    dungeon.getCurLevel()[x][y-1].getBusy().acquire();
    destination = dungeon.getCurLevel()[x][y-1];
    if (!findEnemy(dungeon, x - 1, y) && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        y -= 1;
        dungeon.getCurLevel()[x][y].getBusy().release();
        return;
    }
    dungeon.getCurLevel()[x][y-1].getBusy().release();
}

void Enemy::dropItem(Dungeon &dungeon) noexcept{
    if (isDead()){
        dungeon.getCurLevel()[x][y].setItem(item);
        item = nullptr;
    }
}

void Enemy::getDamage(int damage){
    if (isDead()){
        throw std::invalid_argument("mob is dead");
    }
    cur_hp -= damage;
}

void Enemy::attack(Character *C){
    int damage = rand() % (max_damage - min_damage) + min_damage;
    if (C->isDead()){
        throw std::invalid_argument("hero is dead");
    }
    static_cast<Hero*>(C)->getDamage(damage);
}


