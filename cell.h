#ifndef CELL_H
#define CELL_H

#include "item.h"
#include "chest.h"
#include "enums.h"

class Cell{
    private:
        type_cell type;
        Item *item;
        Chest *chest;

    public:
        Cell() noexcept: type(type_cell::floor), item(nullptr), chest(nullptr){}
        explicit Cell(type_cell t) noexcept: type(t), item(nullptr), chest(nullptr) {}
        explicit Cell(type_cell T, Item *I, Chest *C) noexcept;

        type_cell getType() const noexcept { return type; }
        Item * getItem() const noexcept { return item; }
        Chest * getChest() const noexcept { return chest; }

        Cell& setType(type_cell t) noexcept { type = t; return *this;}
        Cell& setItem(Item *i) noexcept { item = i; return *this; }
        Cell& setChest(Chest *c) noexcept { chest = c; return *this; }

        bool isWall() const noexcept { return type == type_cell::wall; }
        bool isLadder() const noexcept { return type == type_cell::down_ladder || type == type_cell::up_ladder; }
        bool isItem() const noexcept { return item != nullptr; }
        bool isChest() const noexcept { return chest != nullptr; }
        bool isDoor() const noexcept { return type == type_cell::open_door || type == type_cell::close_door; }
        bool isOpenDoor() const noexcept { return type == type_cell::open_door; }
        void changeDoor();

        Cell& operator=(const Cell &c);

};

#endif // CELL_H
