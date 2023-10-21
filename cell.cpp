#include "cell.h"
#include "character.h"
#include "game.h"

Cell::Cell(): type(type_cell::floor){

}
Cell Cell::operator=(const Cell &c){
    type = c.type;
    i = c.i;
    j = c.j;
}
