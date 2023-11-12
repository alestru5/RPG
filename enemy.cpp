#include "enemy.h"
#include "setitem.h"
#include "game.h"
Enemy::Enemy(): Character(), name(name_enemy::white_golem){
    min_damage = SetDamage::createDamage(name_enemy::white_golem).first;
    max_damage = SetDamage::createDamage(name_enemy::white_golem).second;
    item = SetItem::createItem();
}
Enemy::Enemy(int i, int j): Enemy(){
    x = i;
    y = j;
}

Enemy::Enemy(int i, int j, name_enemy n): Character(), name(n){
    min_damage = SetDamage::createDamage(n).first;
    max_damage = SetDamage::createDamage(n).second;
    item = SetItem::createItem();
    x = i;
    y = j;
}

bool Enemy::isNear(){
    int hx = Game::dungeon.getHero().getX();
    int hy = Game::dungeon.getHero().getY();
    if (x == hx && abs(hy - y) == 1 ||
        y == hy && abs(hx - x) == 1){
        return true;
    }
    return false;
}

type_destination Enemy::vision(){
    int hx = Game::dungeon.getHero().getX();
    int hy = Game::dungeon.getHero().getY();
    if (abs(hx - x) >= 5 || abs(hy - y) >= 5 || isNear()){
        return type_destination::none;
    }
    for (int i = std::min(x, hx); i < std::max(x, hx) + 1; i++){
        double j;
        if (hx + 1 - x != 0){
            j = static_cast <double> ((i - x) * (hy + 1 - y) / (hx + 1 - x)) + static_cast<double> (y);
        } else{
            j = hy + 1;
        }

        int u_j = std::floor(j + 1.);
        for (int k = std::min(y, hy); k < u_j; k++){
            if (Game::dungeon.getCurLevel()[i][k].isWall() || Game::dungeon.getCurLevel()[i][k].getType() == type_cell::close_door ||
                Game::dungeon.getCurLevel()[i][k].getItem() != nullptr || Game::dungeon.getCurLevel()[i][k].isChest()){
                return type_destination::none;
            }
        }
    }

    Cell destination = Game::dungeon.getCurLevel()[x-1][y];
    if (x > hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::north;
    }
    destination = Game::dungeon.getCurLevel()[x+1][y];
    if (x < hx && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::south;
    }
    destination = Game::dungeon.getCurLevel()[x][y+1];
    if (y < hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::east;
    }
    destination = Game::dungeon.getCurLevel()[x][y-1];
    if (y > hy && (destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        return type_destination::west;
    }
    return type_destination::none;
}

void Enemy::moveMobDestination(type_destination d){
    if (d == type_destination::north){
        x -= 1;
    } else if (d == type_destination::south){
        x += 1;
    } else if (d == type_destination::east){
        y += 1;
    } else if (d == type_destination::west){
        y -= 1;
    }
}

void Enemy::randomMoveMob(){
    int a = rand() % 4;
    Cell destination = Game::dungeon.getCurLevel()[x - 1][y];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        x -= 1;
        return;
    }
    a = rand() % 3;
    destination = Game::dungeon.getCurLevel()[x+1][y];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        x += 1;
        return;
    }
    a = rand() % 2;
    destination = Game::dungeon.getCurLevel()[x][y+1];
    if (a == 1 && ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
                   destination.getItem() == nullptr)){
        y += 1;
        return;
    }
    destination = Game::dungeon.getCurLevel()[x][y-1];
    if ((destination.getType() == type_cell::floor || destination.isLadder() ||destination.isOpenDoor()) && destination.getChest() == nullptr &&
        destination.getItem() == nullptr){
        y -= 1;
    }
}

void Enemy::enemyAtack(){
    int damage = rand() % (max_damage - min_damage) + min_damage;
    Game::dungeon.getHero().getDamage(damage);
}

/*int Enemy::take_damage(Character *C) const noexcept{
    int damage = min_damage + rand() % (max_damage - min_damage);
    return damage;
}

bool Enemy::get_damage(int damage){
    cur_hp -= damage;
    if (cur_hp <= 0){
        return false;
    }
    return true;
}*/

