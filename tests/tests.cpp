
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "../setchanges.h"
#include "../setcoef.h"
#include "../setcount.h"
#include "../setdamage.h"
#include "../setitem.h"
#include "../setpotion.h"
#include "../setprotect.h"
#include "../matrix.h"
#include "../cell.h"
#include "../artifact.h"
#include "../hero.h"
#include "../bunch.h"
#include "../dungeon.h"
#include "../character.h"
#include "../chest.h"
#include "../game.h"
#include "../enchantment.h"
#include "../enemy.h"
#include "../equipment.h"
#include "../equipmentartifact.h"
#include "../game.h"
#include "../table.h"
#include "../potion.h"
#include "../weapon.h"
#include "../weaponartifact.h"
#include "../weaponartifactenchantment.h"
#include "../weaponenchantment.h"
#include "../item.h"
#include "../matrix2.h"

#include <iostream>
using namespace std;

TEST_CASE("MATRIX"){
    Matrix2<Cell> cn;
    Matrix2<Cell> cM1(10, 10, Cell(type_cell::floor));
    Matrix2<Cell> cM2(10, 10, Cell(type_cell::wall));
    Matrix2<Cell> cM3(10, 10, Cell(type_cell::open_door));
    Matrix2<Cell> cM4(10, 10, Cell(type_cell::close_door));

    Matrix2<Cell> cM5(cM1);
    REQUIRE(cM1.getM() == cM5.getM());
    REQUIRE(cM1.getN() == cM5.getN());

    Matrix2<Cell> cM7(10, 10, Cell(type_cell::floor));
    Matrix2<Cell> cM6(std::move(cM7));
    REQUIRE(cM1.getM() == 10);
    REQUIRE(cM1.getN() == 10);
    REQUIRE(cM7.getM() == 0);
    REQUIRE(cM7.getN() == 0);

    Matrix2<Cell> cM8(10, 10, Cell(type_cell::floor));
    Matrix2<Cell> cM9(cM8.begin(), cM8.end());
    REQUIRE(cM9.getM() == 1);
    REQUIRE(cM9.getN() == 100);

    REQUIRE(cM3.insert_cols(cM3.begin() + cM3.getN(), cM4.begin(), cM4.end()) == cM3.begin() + cM3.getN() - 10);
    REQUIRE(cM1.insert_rows(cM1.begin(), cM2.begin(), cM2.end()) == cM1.begin());
    REQUIRE(cM1.insert_cols(cM1.begin() + cM1.getN(), cM3.begin(), cM3.end()) == cM1.begin() + cM1.getN() - 10);
    REQUIRE(cM1.getM() == 20);
    REQUIRE(cM1.getN() == 20);

    Cell *ca = new Cell[20];
    for (int i = 0; i < 20; i++){
        ca[i] = Cell();
    }
    REQUIRE(cM1.insert_rows(cM1.end(), 10, ca) == cM1.end() - 10 * cM1.getN());

    Cell *cb = new Cell[30];
    for (int i = 0; i < 30; i++){
        cb[i] = Cell();
    }
    REQUIRE(cM1.insert_cols(cM1.begin() + cM1.getN(), 10, cb) == cM1.begin() + cM1.getN() - 10);

    REQUIRE(cM1.erase_rows(cM1.end() - cM1.getN()) == cM1.end());
    REQUIRE(cM1.erase_rows(cM1.end()) == cM1.end());
    REQUIRE(cM1.erase_rows(cM1.end() - 2 * cM1.getN()) == cM1.end() - cM1.getN());

    REQUIRE(cM1.erase_cols(cM1.begin() + cM1.getN()) == cM1.begin() + cM1.getN());
    REQUIRE(cM1.erase_cols(cM1.begin() + cM1.getN() - 1) == cM1.begin() + cM1.getN());
    REQUIRE(cM1.erase_cols(cM1.begin() + cM1.getN() - 3) == cM1.begin() + cM1.getN() - 2);

    REQUIRE(cM1.erase_rows(cM1.begin(), cM1.begin() + 2 * cM1.getN()) == cM1.begin() + 2 * cM1.getN());
    REQUIRE(cM1.erase_rows(cM1.end(), cM1.end()) == cM1.end());
    REQUIRE(cM1.erase_rows(cM1.end() - 5 * cM1.getN(), cM1.end()) == cM1.end());

    REQUIRE(cM1.erase_cols(cM1.begin(), cM1.begin() + 2) == cM1.begin() + 2);
    REQUIRE(cM1.erase_cols(cM1.begin(), cM1.begin() + 10) == cM1.begin() + 10);
    REQUIRE(cM1.erase_cols(cM1.begin() + 1, cM1.begin() + 5) == cM1.begin() + 5);

    std::cout<<"--------------------------------------\n";
    Matrix2<int> n;
    Matrix2<int> M1(10, 10, 0);
    Matrix2<int> M2(10, 10, 1);
    Matrix2<int> M3(10, 10, 2);
    Matrix2<int> M4(10, 10, 3);

    Matrix2<int> M5(M1);
    REQUIRE(M1.getM() == M5.getM());
    REQUIRE(M1.getN() == M5.getN());

    Matrix2<int> M7(10, 10, 0);
    Matrix2<int> M6(std::move(M7));
    REQUIRE(M1.getM() == 10);
    REQUIRE(M1.getN() == 10);
    REQUIRE(M7.getM() == 0);
    REQUIRE(M7.getN() == 0);

    Matrix2<int> M8(10, 10, 0);
    Matrix2<int> M9(M8.begin(), M8.end());
    REQUIRE(M9.getM() == 1);
    REQUIRE(M9.getN() == 100);

    Matrix2<int> M10({6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,6, 6, 6, 6, 6});
    REQUIRE(M10.getM() == 1);
    REQUIRE(M10.getN() == 30);

    REQUIRE(M3.insert_cols(M3.begin() + M3.getN(), M4.begin(), M4.end()) == M3.begin() + M3.getN() - 10);
    REQUIRE(M1.insert_rows(M1.begin(), M2.begin(), M2.end()) == M1.begin());
    REQUIRE(M1.insert_cols(M1.begin() + M1.getN(), M3.begin(), M3.end()) == M1.begin() + M1.getN() - 10);
    REQUIRE(M1.getM() == 20);
    REQUIRE(M1.getN() == 20);x

    
    for (int i = 0; i < M1.getM(); i++){
        for (int j = 0; j < M1.getN(); j++){
            if (i < 10){
                if (j >= 10){
                    REQUIRE(M1.getMatrix()[i*M1.getN() + j] == 2);
                } else{
                    REQUIRE(M1.getMatrix()[i*M1.getN() + j] == 1);
                }    
            } else{
                if (j >= 10){
                    REQUIRE(M1.getMatrix()[i * M1.getN() + j] == 3);
                } else{
                    REQUIRE(M1.getMatrix()[i * M1.getN() + j] == 0);
                }
                
            }
        }
    }

    int *a = new int[20];
    for (int i = 0; i < 20; i++){
        a[i] = 4;
    }
    REQUIRE(M1.insert_rows(M1.end(), 10, a) == M1.end() - 10 * M1.getN());

    int *b = new int[30];
    for (int i = 0; i < 30; i++){
        b[i] = 5;
    }
    REQUIRE(M1.insert_cols(M1.begin() + M1.getN(), 10, b) == M1.begin() + M1.getN() - 10);

    REQUIRE(M1.insert_rows(M1.end(), {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,6, 6, 6, 6, 6}) == M1.end() - M1.getN());
    REQUIRE(M1.insert_cols(M1.begin() + M1.getN(), {6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 ,6, 6, 6, 6, 6, 6}) == M1.begin() + M1.getN() - 1);

    std::cout<<"------------"<<std::endl;

    for (int i = 0; i < M1.getM(); i++){
        for (int j = 0; j < M1.getN(); j++){
            std::cout<<M1.getMatrix()[i * M1.getN() + j]<<" ";
        }
        std::cout<<std::endl;
    }
    REQUIRE(M1.erase_rows(M1.end() - M1.getN()) == M1.end());
    REQUIRE(M1.erase_rows(M1.end()) == M1.end());
    REQUIRE(M1.erase_rows(M1.end() - 2 * M1.getN()) == M1.end() - M1.getN());

    REQUIRE(M1.erase_cols(M1.begin() + M1.getN()) == M1.begin() + M1.getN());
    REQUIRE(M1.erase_cols(M1.begin() + M1.getN() - 1) == M1.begin() + M1.getN());
    REQUIRE(M1.erase_cols(M1.begin() + M1.getN() - 3) == M1.begin() + M1.getN() - 2);

    REQUIRE(M1.erase_rows(M1.begin(), M1.begin() + 2 * M1.getN()) == M1.begin() + 2 * M1.getN());
    REQUIRE(M1.erase_rows(M1.end(), M1.end()) == M1.end());
    REQUIRE(M1.erase_rows(M1.end() - 5 * M1.getN(), M1.end()) == M1.end());

    REQUIRE(M1.erase_cols(M1.begin(), M1.begin() + 2) == M1.begin() + 2);
    REQUIRE(M1.erase_cols(M1.begin(), M1.begin() + 10) == M1.begin() + 10);
    REQUIRE(M1.erase_cols(M1.begin() + 1, M1.begin() + 5) == M1.begin() + 5);

    for (int i = 0; i < M1.getM(); i++){
        for (int j = 0; j < M1.getN(); j++){
            std::cout<<M1.getMatrix()[i * M1.getN() + j]<<" ";
        }
        std::cout<<std::endl;
    }

}

TEST_CASE("CELL"){
    Cell a;
    Cell b(type_cell::close_door);
    Cell c(type_cell::floor, nullptr, nullptr);
    Item *I = SetItem::createItem();
    Chest *C = new Chest(1, SetItem::createItem());
    REQUIRE_THROWS(Cell(type_cell::wall, I, nullptr));
    REQUIRE_THROWS(Cell(type_cell::floor, I, C));

    REQUIRE(b.getType() == type_cell::close_door);
    REQUIRE(b.getChest() == nullptr);
    REQUIRE(b.getItem() == nullptr);

    REQUIRE_NOTHROW(b.setType(type_cell::floor));
    REQUIRE_NOTHROW(b.setChest(nullptr));
    REQUIRE_NOTHROW(b.setItem(nullptr));

    REQUIRE(b.getType() == type_cell::floor);
    REQUIRE(b.getChest() == nullptr);
    REQUIRE(b.getItem() == nullptr);

    REQUIRE(b.isWall() == false);
    REQUIRE(b.isLadder() == false);
    REQUIRE(b.isItem() == false);
    REQUIRE(b.isChest() == false);
    REQUIRE(b.isDoor() == false);
    REQUIRE(b.isOpenDoor() == false);
    
    a.setType(type_cell::close_door);
    REQUIRE_NOTHROW(a.changeDoor());
    REQUIRE(a.getType() == type_cell::open_door);
    REQUIRE_NOTHROW(a.changeDoor());
    REQUIRE(a.getType() == type_cell::close_door);
    REQUIRE_THROWS(b.changeDoor());

    Cell d;
    REQUIRE_NOTHROW(d = b);
    REQUIRE(d.getChest() == b.getChest());
    REQUIRE(d.getItem() == b.getItem());
    REQUIRE(d.getType() == b.getType());

}

TEST_CASE("ARTIFACT"){
    Hero H;
    Artifact a;
    Artifact b(type_artifact::legendary);
    REQUIRE_NOTHROW(a.SetArtifact_Type(type_artifact::mythical));
    REQUIRE(a.getArtifact_Type() == type_artifact::mythical);
    int ag = H.getTable().getValue(short_characteristic::a);
    int i = H.getTable().getValue(short_characteristic::i);
    int s = H.getTable().getValue(short_characteristic::s);
    int e = H.getTable().getValue(short_characteristic::e);
    REQUIRE_NOTHROW(a.useChanges(H));
    REQUIRE(H.getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(H.getTable().getValue(short_characteristic::i) >= i);
    REQUIRE(H.getTable().getValue(short_characteristic::s) >= s);
    REQUIRE(H.getTable().getValue(short_characteristic::e) >= e);
    REQUIRE_NOTHROW(a.unUseChanges(H));
    REQUIRE(H.getTable().getValue(short_characteristic::a) == ag);
    REQUIRE(H.getTable().getValue(short_characteristic::i) == i);
    REQUIRE(H.getTable().getValue(short_characteristic::s) == s);
    REQUIRE(H.getTable().getValue(short_characteristic::e) == e);
    REQUIRE_NOTHROW(b = a);
    REQUIRE(b.getArtifact_Type() == type_artifact::mythical);
}

TEST_CASE("BUNCH"){
    Dungeon d;
    Bunch a;
    Bunch b(type_bunch::big);
    REQUIRE(b.getBunch_Type() == type_bunch::big);
    REQUIRE(b.getCount() == 3);

    REQUIRE_NOTHROW(a = b);
    REQUIRE(a.getBunch_Type() == b.getBunch_Type());
    REQUIRE(a.getCount() == b.getCount());
    REQUIRE(a.getItem_Type() == b.getItem_Type());

    int c = d.getHero().getC_Bunch();
    REQUIRE_NOTHROW(a.use(d));
    REQUIRE(d.getHero().getC_Bunch() == c + a.getCount());
}

TEST_CASE("CHEST"){
    Hero H;
    Chest a;
    Chest b(2, nullptr);
    REQUIRE_THROWS(Chest(-1, nullptr));
    REQUIRE(b.getLevel() == 2);
    REQUIRE(b.getItem() == nullptr);

    REQUIRE_NOTHROW(b.setLevel(3));

    REQUIRE(b.getLevel() == 3);
    REQUIRE(b.getItem() == nullptr);

    REQUIRE_THROWS(b.setLevel(6));
    REQUIRE_NOTHROW(b.setItem(nullptr));

    b.tryToOpen(&H);
    b.tryToOpen(&H);
    b.tryToOpen(&H);
    b.tryToOpen(&H);
    b.tryToOpen(&H);
    b.tryToOpen(&H);
    b.tryToOpen(&H);

    REQUIRE_NOTHROW(a = b); 
    REQUIRE(a.getItem() == b.getItem());
    REQUIRE(a.getLevel() == b.getLevel());
}

TEST_CASE("DUNGEON"){
    Game G;
    Dungeon d;
    Hero H;
    REQUIRE(d.getCount_Levels() == 0);
    REQUIRE(d.getCur_Level() == 0);
    REQUIRE(d.getLevels() == nullptr);
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    REQUIRE(d.getCount_Levels() == 3);
    REQUIRE(d.getCur_Level() == 0);
    REQUIRE(d.getLevels() != nullptr);

    REQUIRE(H.getC_Bunch() == d.getHero().getC_Bunch());
    REQUIRE(H.getCur_Endurance() == d.getHero().getCur_Endurance());
    REQUIRE(H.getCur_Hp() == d.getHero().getCur_Hp());
    REQUIRE(H.getCurr_Chosen_Item() == d.getHero().getCurr_Chosen_Item());
    REQUIRE(H.getExperience() == d.getHero().getExperience());
    REQUIRE(H.getEquipment() == d.getHero().getEquipment());
    REQUIRE(H.getInventory() == d.getHero().getInventory());
    REQUIRE(H.getM_Inventory() == d.getHero().getM_Inventory());
    REQUIRE(H.getMax_Hp() == d.getHero().getMax_Hp());
    REQUIRE(14 == d.getHero().getX());
    REQUIRE(1 == d.getHero().getY());

    REQUIRE_NOTHROW(d.getHero());
    REQUIRE_NOTHROW(d.getEnemies());
    REQUIRE_NOTHROW(d.getCurLevel());

    REQUIRE(d.up_level().getCur_Level() == 1);
    REQUIRE(d.down_level().getCur_Level() == 0);

    int a = d.getEnemies().size();
    REQUIRE_NOTHROW(d.enemyDead(1));
    REQUIRE(d.getEnemies().size() == a - 1);
    REQUIRE_THROWS(d.enemyDead(100));
    REQUIRE(d.getEnemies().size() == a - 1);

    REQUIRE_THROWS(d.move_door(0, 0));
    REQUIRE_THROWS(d.move_door(-1, -100));
    REQUIRE_NOTHROW(d.move_door(6,3));
    REQUIRE(d.getCurLevel()[6][3].getType() == type_cell::open_door);
    REQUIRE_NOTHROW(d.move_door(6,3));
    REQUIRE(d.getCurLevel()[6][3].getType() == type_cell::close_door);
}

TEST_CASE("ENCHANTMENT"){
    Enemy E;
    Enchantment a;
    Enchantment b(type_enchantment::BlackKiller);
    
    REQUIRE(b.getEnchantment_Type() == type_enchantment::BlackKiller);
    REQUIRE_NOTHROW(b.getCoef());

    b.setEnchantment_Type(type_enchantment::RedKiller);
    REQUIRE(b.getEnchantment_Type() == type_enchantment::RedKiller);

    E.setName(name_enemy::black_druid);
    REQUIRE_NOTHROW(b.getMultiply(&E));
    E.setName(name_enemy::blue_wolf);
    REQUIRE_NOTHROW(b.getMultiply(&E));
    E.setName(name_enemy::red_tiger);
    REQUIRE_NOTHROW(b.getMultiply(&E));
    E.setName(name_enemy::white_golem);
    REQUIRE_NOTHROW(b.getMultiply(&E));
    REQUIRE(b.getMultiply(nullptr) == 1);

    REQUIRE_NOTHROW(a = b);
    REQUIRE(a.getEnchantment_Type() == b.getEnchantment_Type());
    E.setName(name_enemy::black_druid);
    REQUIRE(a.getMultiply(&E) == b.getMultiply(&E));
    E.setName(name_enemy::blue_wolf);
    REQUIRE(a.getMultiply(&E) == b.getMultiply(&E));
    E.setName(name_enemy::red_tiger);
    REQUIRE(a.getMultiply(&E) == b.getMultiply(&E));
    E.setName(name_enemy::white_golem);
    REQUIRE(b.getMultiply(&E) == b.getMultiply(&E));
    REQUIRE(a.getMultiply(nullptr) == b.getMultiply(nullptr));
}

TEST_CASE("ENEMY"){
    Game G;
    Dungeon d;
    Hero H;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    Enemy a;
    REQUIRE(a.getName() == name_enemy::white_golem);

    Enemy b(14, 3);
    Enemy e(14, 2);
    Enemy c(14, 14, name_enemy::black_druid);
    REQUIRE(e.isNear(d) == true);
    REQUIRE(c.isNear(d) == false);
    
    REQUIRE(b.vision(d) == type_destination::west);
    REQUIRE(c.vision(d) == type_destination::none);

    d.getCurLevel()[13][14].setType(type_cell::floor);
    d.getCurLevel()[15][14].setType(type_cell::floor);
    d.getCurLevel()[14][13].setType(type_cell::floor);
    d.getCurLevel()[14][15].setType(type_cell::floor);
    d.getCurLevel()[13][14].setChest(nullptr);
    d.getCurLevel()[15][14].setChest(nullptr);
    d.getCurLevel()[14][13].setChest(nullptr);
    d.getCurLevel()[14][15].setChest(nullptr);
    d.getCurLevel()[13][14].setItem(nullptr);
    d.getCurLevel()[15][14].setItem(nullptr);
    d.getCurLevel()[14][13].setItem(nullptr);
    d.getCurLevel()[14][15].setItem(nullptr);

    REQUIRE_NOTHROW(c.move(type_destination::west, d));
    REQUIRE(c.getY() == 13);
    REQUIRE(c.getX() == 14);
    c.setX(14);
    c.setY(14);
    REQUIRE_NOTHROW(c.move(type_destination::east, d));
    REQUIRE(c.getY() == 15);
    REQUIRE(c.getX() == 14);
    c.setX(14);
    c.setY(14);
    REQUIRE_NOTHROW(c.move(type_destination::north, d));
    REQUIRE(c.getX() == 13);
    REQUIRE(c.getY() == 14);
    c.setX(14);
    c.setY(14);
    REQUIRE_NOTHROW(c.move(type_destination::south, d));
    REQUIRE(c.getX() == 15);
    REQUIRE(c.getY() == 14);
    c.setX(14);
    c.setY(14);

    REQUIRE_NOTHROW(c.randomMoveMob(d));
    REQUIRE(c.getX() <= 15);
    REQUIRE(c.getX() >= 13);
    REQUIRE(c.getY() >= 13);
    REQUIRE(c.getY() <= 15);
    c.setCur_Hp(0);
    REQUIRE_NOTHROW(c.move(type_destination::north, d));

    c.setX(14);
    c.setY(14);
    d.getCurLevel()[13][14].setType(type_cell::wall);
    d.getCurLevel()[15][14].setType(type_cell::wall);
    d.getCurLevel()[14][13].setType(type_cell::wall);
    d.getCurLevel()[13][15].setType(type_cell::wall);
    REQUIRE_NOTHROW(c.randomMoveMob(d));
    REQUIRE(c.vision(d) == type_destination::none);

    REQUIRE(c.getX() == 14);
    REQUIRE(c.getY() == 14);

    REQUIRE_NOTHROW(e.randomMoveMob(d));
    REQUIRE_NOTHROW(e.randomMoveMob(d));
    REQUIRE_NOTHROW(e.randomMoveMob(d));
    REQUIRE_NOTHROW(e.randomMoveMob(d));
    REQUIRE_NOTHROW(e.randomMoveMob(d));
    REQUIRE(e.getX() <= 19);
    REQUIRE(e.getX() >= 9);
    REQUIRE(e.getY() >= 0);
    REQUIRE(e.getY() <= 8);

    REQUIRE_NOTHROW(c.dropItem(d));
    REQUIRE(c.getItem() == nullptr);

    c.setCur_Hp(100);
    REQUIRE_NOTHROW(c.getDamage(10));
    REQUIRE(c.getCur_Hp() == 90);

    REQUIRE_NOTHROW(b.attack(static_cast<Character *>(&H)));
    REQUIRE(H.getCur_Hp() <= 100);
    H.setCur_Hp(0);
    REQUIRE_THROWS(b.attack(static_cast<Character *>(&H)));

    REQUIRE_NOTHROW(c.dropItem(d));
    REQUIRE(c.getItem() == nullptr);
    H.setX(12);
    H.setY(2);
    a.setX(13);
    a.setY(2);
    REQUIRE(a.vision(d) == type_destination::south);

    c.setCur_Hp(0);
    REQUIRE_THROWS(c.getDamage(10));
}

TEST_CASE("EQUIPMENT"){
    Game G;
    Dungeon d;
    Hero H;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    Equipment a;
    Equipment b(name_equipment::diamond, type_equipment::boots);

    REQUIRE_NOTHROW(a.setNameType(name_equipment::gold, type_equipment::helmet));
    REQUIRE(a.getEquipment_Name() == name_equipment::gold);
    REQUIRE(a.getEquipment_Type() == type_equipment::helmet);

    Equipment c;
    REQUIRE_NOTHROW(c = a);
    REQUIRE(c.getEquipment_Name() == a.getEquipment_Name());
    REQUIRE(c.getEquipment_Type() == a.getEquipment_Type());
    REQUIRE(c.getItem_Type() == a.getItem_Type());
    REQUIRE(c.getMax_Protect() == a.getMax_Protect());
    REQUIRE(c.getMin_Protect() == a.getMin_Protect());

    REQUIRE_NOTHROW(a.getProtect());
    REQUIRE_NOTHROW(a.use(d));

    REQUIRE_NOTHROW(c.setNameType(name_equipment::diamond, type_equipment::bib));
    std::list<Equipment*> tmp;
    tmp.push_back(&a);
    tmp.push_back(&c);
    H.setEquipment(tmp);
    REQUIRE_NOTHROW(a.use(d));
    REQUIRE_NOTHROW(c.use(d));
    REQUIRE(d.getHero().getEquipment() == tmp);
    REQUIRE_NOTHROW(a.getMin_Protect());
    REQUIRE_NOTHROW(a.getMax_Protect());

    EquipmentArtifact *EA = new EquipmentArtifact(name_equipment::diamond, type_equipment::bib, type_artifact::legendary);
    std::list<Equipment*> tmp2;
    tmp2.push_back(static_cast<Equipment*>(EA));
    d.getHero().setEquipment(tmp2);
    REQUIRE_NOTHROW(c.use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);

}

TEST_CASE("EQUIPMENT ARTIFACT"){
    Game G;
    Dungeon d;
    Hero H;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    EquipmentArtifact a;
    EquipmentArtifact b(name_equipment::diamond, type_equipment::boots, type_artifact::legendary);

    REQUIRE_NOTHROW(a.setNameType(name_equipment::gold, type_equipment::helmet));
    REQUIRE(a.getEquipment_Name() == name_equipment::gold);
    REQUIRE(a.getEquipment_Type() == type_equipment::helmet);

    EquipmentArtifact c;
    REQUIRE_NOTHROW(c = a);
    REQUIRE(c.getEquipment_Name() == a.getEquipment_Name());
    REQUIRE(c.getEquipment_Type() == a.getEquipment_Type());
    REQUIRE(c.getArtifact_Type() == a.getArtifact_Type());
    REQUIRE(c.getItem_Type() == a.getItem_Type());
    REQUIRE(c.getMax_Protect() == a.getMax_Protect());
    REQUIRE(c.getMin_Protect() == a.getMin_Protect());

    REQUIRE_NOTHROW(a.getProtect());
    REQUIRE_NOTHROW(a.use(d));

    REQUIRE_NOTHROW(c.setNameType(name_equipment::diamond, type_equipment::bib));
    std::list<Equipment*> tmp;
    tmp.push_back(&a);
    tmp.push_back(&c);
    H.setEquipment(tmp);
    REQUIRE_NOTHROW(a.use(d));
    REQUIRE_NOTHROW(c.use(d));
    REQUIRE(d.getHero().getEquipment() == tmp);
    REQUIRE_NOTHROW(a.getMin_Protect());
    REQUIRE_NOTHROW(a.getMax_Protect());

    EquipmentArtifact *EA = new EquipmentArtifact(name_equipment::diamond, type_equipment::bib, type_artifact::legendary);
    std::list<Equipment*> tmp2;
    tmp2.push_back(static_cast<Equipment*>(EA));
    d.getHero().setEquipment(tmp2);
    REQUIRE_NOTHROW(c.use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}

TEST_CASE("GAME"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    REQUIRE_NOTHROW(G.getDungeon());
    REQUIRE(G.getIsGame() == false);

    REQUIRE_NOTHROW(G.setMapHeight(32));
    REQUIRE_NOTHROW(G.setMapHeight(16));

    REQUIRE(G.getMapWidth() == 32);
    REQUIRE(G.getMapHeight() == 16);

    REQUIRE_NOTHROW(G.initGame());
    REQUIRE(G.tick(d) == true);
    G.getDungeon().getHero().setCur_Hp(0);
    REQUIRE(G.tick(G.getDungeon()) == false);

    REQUIRE_NOTHROW(G.actionMobs(G.getDungeon()));
    REQUIRE((G.getDungeon().getEnemies()[0].second != d.getEnemies()[0].second));
}

TEST_CASE("HERO"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();
    Enemy E;

    Hero a;
    Hero b(1, 1);
    Hero c(a);
    a.setX(14);
    a.setY(1);

    Hero H;
    Hero H2;
    REQUIRE_THROWS(H.setY(-5));
    REQUIRE_THROWS(H.setX(-5));
    REQUIRE_THROWS(H.setMax_Hp(-5));
    REQUIRE_THROWS(H.setCur_Hp(-5));
    REQUIRE_NOTHROW(H2 = H);
    REQUIRE(H.getY() == H2.getY());
    REQUIRE(H.getX() == H2.getX());
    REQUIRE(H.getExperience() == H2.getExperience());
    REQUIRE(H.getMax_Hp() == H2.getMax_Hp());
    REQUIRE(H.getCur_Hp() == H2.getCur_Hp());

    REQUIRE_NOTHROW(a.setWeapon(nullptr));
    REQUIRE(a.getWeapon() == nullptr);

    REQUIRE_NOTHROW(a.setCurr_Chosen_Item(1));
    REQUIRE_THROWS(a.setCurr_Chosen_Item(-1));
    REQUIRE_NOTHROW(a.setC_Bunch(10));
    REQUIRE(a.getC_Bunch() == 10);
    REQUIRE_THROWS(a.setC_Bunch(-4));

    REQUIRE_NOTHROW(a.setCur_Endurance(10));
    REQUIRE(a.getCur_Endurance() == 10);
    REQUIRE_THROWS(a.setCur_Endurance(-4));

    REQUIRE_NOTHROW(b = a);

    REQUIRE_NOTHROW(a.nextChosenItem());
    REQUIRE(a.getCurr_Chosen_Item() == 2);
    REQUIRE_NOTHROW(a.fullProtect());
    REQUIRE_NOTHROW(a.minProtect());
    REQUIRE_NOTHROW(a.maxProtect());
    REQUIRE_NOTHROW(a.minDamage());
    REQUIRE_NOTHROW(a.maxDamage());
    REQUIRE_NOTHROW(a.getDamage(10));
    REQUIRE(a.getCur_Hp() == 95);

    REQUIRE_NOTHROW(a.findEnemy(d));

    REQUIRE_NOTHROW(a.fullDamage(&E));

    a.setCur_Endurance(10);
    int t = a.getCur_Endurance();
    REQUIRE_NOTHROW(a.updateEndurance());
    REQUIRE(a.getCur_Endurance() == 30);

    int e = a.getExperience();
    REQUIRE_NOTHROW(a.addExperience(4));
    REQUIRE(a.getExperience() == e + 4);

    REQUIRE_THROWS(a.addExperience(-5));

    int ag = a.getTable().getValue(short_characteristic::a);
    a.setExperience(200);
    REQUIRE_NOTHROW(a.levelUp(short_characteristic::a));
    REQUIRE(a.getTable().getValue(short_characteristic::a) == ag + 5);

    REQUIRE_NOTHROW(a.usingChosenItem(d));

    REQUIRE_NOTHROW(a.attack(&E));

    a.setX(8);
    a.setY(6);

    d.getCurLevel()[7][6].setItem(SetItem::createItem());
    d.getCurLevel()[8][5].setItem(SetItem::createItem());
    d.getCurLevel()[8][7].setItem(SetItem::createItem());
    d.getCurLevel()[9][6].setItem(SetItem::createItem());

    REQUIRE_NOTHROW(a.take(d));
    d.getCurLevel()[8][7].setItem(nullptr);
    REQUIRE_NOTHROW(a.take(d));
    d.getCurLevel()[8][5].setItem(nullptr);
    REQUIRE_NOTHROW(a.take(d));
    d.getCurLevel()[9][6].setItem(nullptr);
    REQUIRE_NOTHROW(a.take(d));
    d.getCurLevel()[7][6].setItem(nullptr);

    REQUIRE_NOTHROW(a.move(type_destination::east, d));
    REQUIRE_NOTHROW(a.move(type_destination::west, d));
    REQUIRE_NOTHROW(a.move(type_destination::south, d));
    REQUIRE_NOTHROW(a.move(type_destination::north, d));

    REQUIRE(a.getX() == 8);
    REQUIRE(a.getY() == 6);
    Chest C;
    d.getCurLevel()[7][6].setChest(&C);
    d.getCurLevel()[8][5].setChest(&C);
    d.getCurLevel()[8][7].setChest(&C);
    d.getCurLevel()[9][6].setChest(&C);
    
    a.open_chest(d);
    d.getCurLevel()[8][7].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[8][5].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[9][6].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[7][6].setChest(nullptr);

    d.getCurLevel()[7][6].setChest(&C);
    d.getCurLevel()[8][5].setChest(&C);
    d.getCurLevel()[8][7].setChest(&C);
    d.getCurLevel()[9][6].setChest(&C);
    
    a.open_chest(d);
    d.getCurLevel()[8][7].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[8][5].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[9][6].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[7][6].setChest(nullptr);

    d.getCurLevel()[7][6].setChest(&C);
    d.getCurLevel()[8][5].setChest(&C);
    d.getCurLevel()[8][7].setChest(&C);
    d.getCurLevel()[9][6].setChest(&C);
    
    a.open_chest(d);
    d.getCurLevel()[8][7].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[8][5].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[9][6].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[7][6].setChest(nullptr);

    d.getCurLevel()[7][6].setChest(&C);
    d.getCurLevel()[8][5].setChest(&C);
    d.getCurLevel()[8][7].setChest(&C);
    d.getCurLevel()[9][6].setChest(&C);
    
    a.open_chest(d);
    d.getCurLevel()[8][7].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[8][5].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[9][6].setChest(nullptr);
    a.open_chest(d);
    d.getCurLevel()[7][6].setChest(nullptr);

    d.getCurLevel()[7][6].setType(type_cell::open_door);
    d.getCurLevel()[8][5].setType(type_cell::open_door);
    d.getCurLevel()[8][7].setType(type_cell::open_door);
    d.getCurLevel()[9][6].setType(type_cell::open_door);
    

    REQUIRE(a.getX() == 8);
    REQUIRE(a.getY() == 6);
    REQUIRE_NOTHROW(a.change_door(d));
    d.getCurLevel()[8][7].setType(type_cell::floor);
    REQUIRE_NOTHROW(a.change_door(d));
    d.getCurLevel()[8][5].setType(type_cell::floor);
    REQUIRE_NOTHROW(a.change_door(d));
    d.getCurLevel()[9][6].setType(type_cell::floor);
    REQUIRE_NOTHROW(a.change_door(d));
    d.getCurLevel()[7][6].setType(type_cell::floor);

    a.setMax_Hp(100);

    d.getHero().setX(7);
    d.getHero().setY(6);
    d.getCurLevel()[7][6].setType(type_cell::down_ladder);
    d.getLevels()[d.getCur_Level() + 1][7][6].setType(type_cell::up_ladder);
    REQUIRE_NOTHROW(d.getHero().climb(d));
    REQUIRE_NOTHROW(d.getHero().climb(d));
}

TEST_CASE("TABLE"){
    Table a;
    Table b(a);
    REQUIRE_NOTHROW(a.setValue(short_characteristic::a, 5));
    REQUIRE_THROWS(a.setValue(short_characteristic::a, -5));
    REQUIRE_NOTHROW(a.setValue(short_characteristic::e, 5));
    REQUIRE_NOTHROW(a.setValue(short_characteristic::i, 5));
    REQUIRE_NOTHROW(a.setValue(short_characteristic::s, 5));

    REQUIRE_NOTHROW(a.setValue(full_characteristic::agility, 5));
    REQUIRE_NOTHROW(a.setValue(full_characteristic::strength, 5));
    REQUIRE_NOTHROW(a.setValue(full_characteristic::endurance, 5));
    REQUIRE_NOTHROW(a.setValue(full_characteristic::intelligence, 5));

    REQUIRE(a.getValue(short_characteristic::a) == 5);
    REQUIRE(a.getValue(short_characteristic::e) == 5);
    REQUIRE(a.getValue(short_characteristic::s) == 5);
    REQUIRE(a.getValue(short_characteristic::i) == 5);
}

TEST_CASE("POTION"){
    Potion a;
    Potion b(name_potion::experience);

    REQUIRE(b.getPotion_Name() == name_potion::experience);
    REQUIRE_NOTHROW(b.getChanges());

    REQUIRE_NOTHROW(b = a);

    REQUIRE(b.getChanges() == a.getChanges());
    REQUIRE(b.getItem_Type() == a.getItem_Type());
    REQUIRE(b.getPotion_Name() == a.getPotion_Name());

    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();

    Potion p1(name_potion::agility);
    Potion p2(name_potion::endurance);
    Potion p3(name_potion::hp);
    Potion p4(name_potion::intelligence);
    Potion p5(name_potion::strength);
    
    REQUIRE_NOTHROW(a.use(d));
    REQUIRE_NOTHROW(p1.use(d));
    REQUIRE_NOTHROW(p2.use(d));
    REQUIRE_NOTHROW(p3.use(d));
    REQUIRE_NOTHROW(p4.use(d));
    REQUIRE_NOTHROW(p5.use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}

TEST_CASE("WEAPON"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();
    Enemy E;

    d.getHero().setWeapon(nullptr);
    Weapon a;
    Weapon b(name_weapon::nunchucks);
    Weapon *c = new Weapon(name_weapon::nunchucks);
    WeaponArtifact *wa = new WeaponArtifact(name_weapon::knife);
    WeaponArtifactEnchantment *we = new WeaponArtifactEnchantment();

    REQUIRE_NOTHROW(b.setName(name_weapon::sword));
    REQUIRE_NOTHROW(a = b);
    REQUIRE(a.getItem_Type() == b.getItem_Type());
    REQUIRE(a.getMax_Damage() == b.getMax_Damage());
    REQUIRE(a.getWeapon_Name() == b.getWeapon_Name());

    REQUIRE_NOTHROW(b.getDamage(&E));
    REQUIRE_NOTHROW(c->use(d));
    REQUIRE_NOTHROW(wa->use(d));
    REQUIRE_NOTHROW(we->use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}

TEST_CASE("WEAPON ARTIFACT"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();
    Enemy E;

    WeaponArtifact *a = new WeaponArtifact(name_weapon::knife);
    WeaponArtifact b;
    REQUIRE_NOTHROW(a->getDamage(&E));
    REQUIRE_NOTHROW(a->use(d));
    Weapon *c = new Weapon(name_weapon::nunchucks);
    WeaponArtifact *wa = new WeaponArtifact(name_weapon::knife);
    WeaponArtifactEnchantment *we = new WeaponArtifactEnchantment();
    REQUIRE_NOTHROW(c->use(d));
    REQUIRE_NOTHROW(wa->use(d));
    REQUIRE_NOTHROW(we->use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}

TEST_CASE("WEAPON ENCHANTMENT"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();
    Enemy E;

    WeaponEnchantment *a = new WeaponEnchantment(name_weapon::knife);
    REQUIRE_NOTHROW(a->getDamage(&E));
    REQUIRE_NOTHROW(a->use(d));
    Weapon *c = new Weapon(name_weapon::nunchucks);
    WeaponArtifact *wa = new WeaponArtifact(name_weapon::knife);
    WeaponArtifactEnchantment *we = new WeaponArtifactEnchantment();
    d.getHero().setWeapon(wa);
    REQUIRE_NOTHROW(a->use(d));
    d.getHero().setWeapon(we);
    REQUIRE_NOTHROW(a->use(d));
    d.getHero().setWeapon(c);
    REQUIRE_NOTHROW(a->use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}

TEST_CASE ("WEAPON ARTIFACT ENCHANTMENT"){
    Game G;
    Dungeon d;
    std::ifstream lvl;
    lvl.open("/home/alestru/PetProjects/RPG/map.txt");
    d.initializeLevelsFile(lvl, G);
    lvl.close();

    std::ifstream mobs;
    mobs.open("/home/alestru/PetProjects/RPG/enemies.txt");
    d.initializeEnemiesFile(mobs);
    mobs.close();
    Enemy *E = new Enemy();

    WeaponArtifactEnchantment *a = new WeaponArtifactEnchantment(name_weapon::knife, type_artifact::legendary, type_enchantment::BlackKiller);
    REQUIRE_NOTHROW(a->getDamage(E));
    REQUIRE_NOTHROW(a->use(d));
    Weapon *c = new Weapon(name_weapon::nunchucks);
    WeaponArtifact *wa = new WeaponArtifact(name_weapon::knife);
    WeaponEnchantment *t = new WeaponEnchantment();
    
    d.getHero().setWeapon(c);
    REQUIRE_NOTHROW(a->use(d));
    d.getHero().setWeapon(wa);
    REQUIRE_NOTHROW(a->use(d));
    d.getHero().setWeapon(t);
    REQUIRE_NOTHROW(a->use(d));

    int ag = d.getHero().getTable().getValue(short_characteristic::a);
    int en = d.getHero().getTable().getValue(short_characteristic::e);
    int in = d.getHero().getTable().getValue(short_characteristic::i);
    int st = d.getHero().getTable().getValue(short_characteristic::s);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::a) >= ag);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::e) >= en);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::i) >= in);
    REQUIRE(d.getHero().getTable().getValue(short_characteristic::s) >= st);
}


