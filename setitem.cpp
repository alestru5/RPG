#include "setitem.h"
Item *SetItem::createItem(){
    return new Potion(name_potion::agility);
    int a = rand() % 4;
    if (a == 0){
        int b = rand() % 4;
        name_equipment n;
        if (b == 0){
            n = name_equipment::leather;
        } else if (b == 1){
            n = name_equipment::iron;
        } else if (b == 2){
            n = name_equipment::gold;
        } else{
            n = name_equipment::diamond;
        }
        int c =rand() % 4;
        type_equipment t;
        if (c == 0){
            t = type_equipment::boots;
        } else if (c == 1){
            t = type_equipment::leggings;
        } else if (c == 2){
            t = type_equipment::bib;
        } else{
            t = type_equipment::helmet;
        }
        if (rand()%2 == 0){
            return new Equipment(n,t);
        } else{
            int d = rand() % 4;
            type_artifact ta;
            if (d == 0){
                ta = type_artifact::casual;
            } else if (d == 1){
                ta = type_artifact::rare;
            } else if (d == 2){
                ta = type_artifact::mythical;
            } else{
                ta = type_artifact::legendary;
            }
            return new EquipmentArtifact(n, t, ta);
        }

    } else if (a == 1){
        int b = rand() % 3;
        name_weapon n;
        if ( b == 0){
            n = name_weapon::knife;
        } else if (b == 1){
            n = name_weapon::nunchucks;
        } else{
            n = name_weapon::sword;
        }
        type_enchantment te;
        int d = rand() % 4;
        if (d == 0){
            te = type_enchantment::BlackKiller;
        } else if (d == 1){
            te = type_enchantment::BlueKiller;
        } else if (d == 2){
            te = type_enchantment::WhiteKiller;
        } else{
            te = type_enchantment::RedKiller;
        }
        int e = rand() % 4;
        type_artifact ta;
        if (e == 0){
            ta = type_artifact::casual;
        } else if (e == 1){
            ta = type_artifact::rare;
        } else if (e == 2){
            ta = type_artifact::mythical;
        } else{
            ta = type_artifact::legendary;
        }
        int c = rand() % 4;
        if (c == 0){
            return new Weapon(n);
        } else if (c == 1){
            return new WeaponEnchantment(n, te);
        } else if (c == 2){
            return new WeaponArtifact(n, ta);
        } else{
            return new WeaponArtifactEnchantment(n, ta, te);
        }
    } else if (a == 2){
        name_potion n;
        int b = rand() % 5;
        if (b == 0){
            n = name_potion::hp;
        } else if (b == 1){
            n = name_potion::experience;
        } else if (b == 2){
            n = name_potion::agility;
        } else if (b == 3){
            n = name_potion::intelligence;
        } else{
            n = name_potion::strength;
        }
        return new Potion(n);
    } else{
        int b = rand() % 3;
        type_bunch tb;
        if (b == 0){
            tb = type_bunch::small;
        } else if (b == 1){
            tb = type_bunch::medium;
        } else{
            tb = type_bunch::big;
        }
        return new Bunch(tb);
    }
}
