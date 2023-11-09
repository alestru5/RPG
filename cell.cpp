#include "cell.h"
#include "character.h"
#include "game.h"

Cell::Cell(type_cell T, Item *I, Chest *C){
    if (T == type_cell::floor){
        item = I;
        chest = C;
        type = T;
    } else {
        throw std::invalid_argument("Things can put only on floor");
    }
}

bool Cell::isWall() const noexcept{
    if (type == type_cell::wall){
        return true;
    }
    return false;
}

bool Cell::isItem() const noexcept{
    if (item != nullptr){
        return true;
    }
    return false;
}

bool Cell::isChest() const noexcept{
    if (chest != nullptr){
        return true;
    }
    return false;
}

bool Cell::isLadder() const noexcept{
    if (type == type_cell::down_ladder || type == type_cell::up_ladder){
        return true;
    }
    return false;
}

Cell& Cell::operator=(const Cell &c){
    type = c.type;
    item = c.item;
    chest = c.chest;
    return *this;
}


