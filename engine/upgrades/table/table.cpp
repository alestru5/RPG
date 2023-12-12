#include "table.h"

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
    return -1;
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


