#include "enumtostring.h"

std::string EnumToString::toString(name_weapon n){
    if (n == name_weapon::knife){
        return "Knife";
    } else if (n == name_weapon::nunchucks){
        return "Nunchucks";
    } else{
        return "Sword";
    }
}

std::string EnumToString::toString(type_artifact t){
    if (t == type_artifact::casual){
        return "Casual";
    } else if (t == type_artifact::rare){
        return "Rare";
    } else if (t == type_artifact::mythical){
        return "Mythical";
    } else {
        return "Legendary";
    }
}

std::string EnumToString::toString(type_enchantment t){
    if (t == type_enchantment::BlackKiller){
        return "BlackKiller";
    } else if (t == type_enchantment::BlueKiller){
        return "BlueKiller";
    } else if (t == type_enchantment::RedKiller){
        return "RedKiller";
    } else{
        return "WhiteKiller";
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
        res += "Diamond ";
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
    } else if (n == name_potion::strength){
        return "Strength";
    } else if (n == name_potion::endurance){
        return "Endurance";
    }
}
