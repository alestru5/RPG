#include "enumtostring.h"

std::string EnumToString::toString(name_weapon n){
    if (n == name_weapon::knife){
        return "Knife";
    } else if (n == name_weapon::nunchucks){
        return "Nunchucks";
    } else if (n == name_weapon::sword){
        return "Sword";
    }
}
std::string EnumToString::toString(name_equipment n, type_equipment t){
    std::string res;
    if (n == name_equipment::leather){
        res += "Leather ";
    } else if (n == name_equipment::iron){
        res += "Iron ";
    } else if (n == name_equipment::gold){
        res += "Gold ";
    } else if (n == name_equipment::diamond){
        res += "Diamond";
    }
    if (t == type_equipment::boots){
        res += "boots";
    } else if (t == type_equipment::leggings){
        res += "leggings";
    } else if (t == type_equipment::bib){
        res += "bib";
    } else if (t == type_equipment::helmet){
        res += "helmet";
    }
    return res;
}

std::string EnumToString::toString(name_potion n){
    if (n == name_potion::agility){
        return "Agility";
    } else if (n == name_potion::experience){
        return "Experience";
    } else if (n == name_potion::hp){
        return "Hp";
    } else if (n == name_potion::intelligence){
        return "Intelligence";
    } else{
        return "Strength";
    }
}
