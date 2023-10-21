#include "character.h"
#include "game.h"

Character::Character(int i, int j){
    x = i;
    y = j;
}

bool Character::move(std::string direction){
    Cell destination;
    int i2 = x, j2 = y;
    if (direction == "south"){
        destination = Game::dungeon.getLevels()[0][x + 1][y];
        i2 += 1;
    } else if (direction == "east"){
        destination = Game::dungeon.getLevels()[0][x][y + 1];
        j2 += 1;
    } else if (direction == "west"){
        destination = Game::dungeon.getLevels()[0][x][y -1];
        j2 -= 1;
    } else if (direction == "north"){
        destination = Game::dungeon.getLevels()[0][x-1][y];
        i2 -= 1;
    } else{
        return false;
    }
    if (destination.getType() != type_cell::wall){
        Game::dungeon.getLevels()[0].swap(x, y, i2, j2);
        x = i2;
        y = j2;
        return true;
    }
    return false;
}
