#include "table.h"

Table::Table() noexcept{
    table[std::make_pair("strength", "s")] = 50;
    table[std::make_pair("agility", "a")] = 50;
    table[std::make_pair("endurance", "e")] = 100;
    table[std::make_pair("intelligence", "i")] = 50;
}

Table::Table(const Table& T) noexcept{
    for (auto &i: T.table){
        table[i.first] = i.second;
    }
}


int Table::getValue(std::string name) const noexcept{
    for (auto &i: table){
        if (i.first.first == name){
            return i.second;
        }
        if (i.first.second == name){
            return i.second;
        }
    }
    return 0;
}

Table& Table::setValue(std::string name, int v){
    if (v < 0){
        throw std::invalid_argument("negative value");
    }
    for (auto i: table){
        if (i.first.first == name || i.first.second == name){
            i.second = v;
        }
    }

    return *this;
}


