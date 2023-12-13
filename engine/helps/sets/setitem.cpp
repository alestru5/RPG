#include "setitem.h"

Item *SetItem::createItem(){
    int a = rand() % 4;
    if (a == 0){
        int b = rand() % 4;
        std::string n;
        if (b == 0){
            n = "leather";
        } else if (b == 1){
            n = "iron";
        } else if (b == 2){
            n = "gold";
        } else{
            n = "diamond";
        }
        int c =rand() % 4;
        std::string t;
        if (c == 0){
            t = "boots";
        } else if (c == 1){
            t = "leggings";
        } else if (c == 2){
            t = "bib";
        } else{
            t = "helmet";
        }
        if (rand()%2 == 0){
            return new Equipment(n, t, 1, 5);
        } else{
            int d = rand() % 4;
            std::string ta;
            if (d == 0){
                ta = "casual";
            } else if (d == 1){
                ta = "rare";
            } else if (d == 2){
                ta = "mythical";
            } else{
                ta = "legendary";
            }
            std::list<std::pair<std::string, int>> tmp2;
            tmp2.push_back(std::make_pair("strength", 5));
            return new EquipmentArtifact(n, t, 1, 5, 5, ta, tmp2);
        }

    } else if (a == 1){
        int b = rand() % 3;
        std::string n;
        if ( b == 0){
            n = "knife";
        } else if (b == 1){
            n = "nunchucks";
        } else{
            n ="sword";
        }
        std::string te;
        int d = rand() % 4;
        if (d == 0){
            te = "BlackKiller";
        } else if (d == 1){
            te = "BlueKiller";
        } else if (d == 2){
            te = "WhiteKiller";
        } else{
            te = "RedKiller";
        }
        int e = rand() % 4;
        std::string ta;
        if (e == 0){
            ta = "casual";
        } else if (e == 1){
            ta = "rare";
        } else if (e == 2){
            ta = "mythical";
        } else{
            ta = "legendary";
        }
        int c = rand() % 4;
        if (c == 0){
            return new Weapon(n, 1, 5);
        } else if (c == 1){
            std::list<std::pair<std::string, double>> tmp;
            tmp.push_back(std::make_pair("BlackKiller", 1.5));
            return new WeaponEnchantment(n, 1, 5, te, tmp);
        } else if (c == 2){
            std::list<std::pair<std::string, int>> tmp2;
            tmp2.push_back(std::make_pair("strength", 5));
            return new WeaponArtifact(n, 1, 5, 5, ta, tmp2);
        } else{
            std::list<std::pair<std::string, double>> tmp;
            tmp.push_back(std::make_pair("BlackKiller", 1.5));
            std::list<std::pair<std::string, int>> tmp2;
            tmp2.push_back(std::make_pair("strength", 5));
            return new WeaponArtifactEnchantment(n, 1, 5, 5, ta, tmp2, te, tmp);
        }
    } else if (a == 2){
        std::string n;
        int b = rand() % 6;
        if (b == 0){
            n = "hp";
        } else if (b == 1){
            n = "experience";
        } else if (b == 2){
            n = "agility";
        } else if (b == 3){
            n = "intelligence";
        } else if (b == 4){
            n = "strength";
        } else{
            n = "endurance";
        }
        return new Potion(n, std::make_pair(n, 5));
    } else{
        int b = rand() % 3;
        std::string tb;
        int d;
        if (b == 0){
            tb = "small";
            d = 1;
        } else if (b == 1){
            tb = "medium";
            d = 2;
        } else{
            tb = "big";
            d = 3;
        }
        return new Bunch(tb, d);
    }
}
