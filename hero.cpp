#include "hero.h"
Hero::Hero(): Character(), level(0), experience(0), characteristic(100, 10, 10, 10, 10, 10){}
Hero::Hero(int i, int j): level(0), experience(0), characteristic(100, 10, 10, 10, 10, 10){
    x = i;
    y = j;
}
int Hero::act(std::string key){
    std::string command = "invalid";
    if (key == "w") command = "north";
    else if (key == "s") command = "south";
    else if (key == "d") command = "east";
    else if (key == "a") command = "west";
    else if (key == "e") command = "attack";
    else if (key == "q") command = "switch";
    else if (key == "f") command = "drop";
    else if (key == "r") command = "pick";

    if(move(command)){
        return 1;
    }
    return 0;
}

Hero Hero::operator = (const Hero &H){
    x = H.x;
    y = H.y;
    level = H.level;
    experience = H.experience;
    characteristic = H.characteristic;
}

