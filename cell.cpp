#include "cell.h"
#include "character.h"
#include "game.h"

Cell::Cell(type_cell T, Item *I, Chest *C){
    if (T != type_cell::floor){
        throw std::invalid_argument("Things can put only on floor");
    }
    item = I;
    chest = C;
    type = T;
}

void Cell::changeDoor(){
    if (type == type_cell::close_door){
        type = type_cell::open_door;
    } else if (type == type_cell::open_door){
        type = type_cell::close_door;
    } else{
        throw std::runtime_error("Its not door");
    }
}

Cell& Cell::operator=(const Cell &c){
    type = c.type;
    item = c.item;
    chest = c.chest;
    return *this;
}


