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
        Cell(): type(type_cell::floor), item(nullptr), chest(nullptr){}
        explicit Cell(type_cell t) noexcept: type(t), item(nullptr), chest(nullptr) {}
        explicit Cell(type_cell T, Item *I, Chest *C);


        type_cell getType() const noexcept {return type; }
        Item * getItem() const noexcept { return item; }
        Chest * getChest() const noexcept { return chest; }

        Cell& setType(type_cell t) noexcept { type = t; return *this;}
        Cell& setItem(Item *i) noexcept { item = i; return *this; }
        Cell& setChest(Chest *c) noexcept { chest = c; return *this; }

        bool isWall() const noexcept;
        bool isItem() const noexcept;
        bool isChest() const noexcept;

        Cell& operator=(const Cell &c);

};

#endif // CELL_H
