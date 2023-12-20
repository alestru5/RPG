#include "cell.h"
#include "../../item/item.h"
#include "chest.h"

Cell::Cell(type_cell T, Item *I, Chest *C){
    if (T != type_cell::floor && I != nullptr){
        throw std::invalid_argument("Things can put only on floor");
    }
    if (I != nullptr && C != nullptr){
        throw std::invalid_argument("and item and chest cannot be on one cell");
    }
    item = I;
    chest = C;
    type = T;
}

Cell::Cell(const Cell &C){
    type = C.type;
    item = C.item;
    chest = C.chest;
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
    Cell();
    type = c.type;
    item = c.item;
    chest = c.chest;
    return *this;
}



