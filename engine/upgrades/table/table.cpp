#include "table.h"

Table::Table() noexcept{
    table[std::make_pair(full_characteristic::strength, short_characteristic::s)] = 50;
    table[std::make_pair(full_characteristic::agility, short_characteristic::a)] = 50;
    table[std::make_pair(full_characteristic::endurance, short_characteristic::e)] = 10000000;
    table[std::make_pair(full_characteristic::intelligence, short_characteristic::i)] = 50;
}


Table::Table(const Table& T) noexcept{
    for (auto &i: T.table){
        table[i.first] = i.second;
    }
}


int Table::getValue(full_characteristic name) const noexcept{
    for (auto &i: table){
        if (i.first.first == name){
            return i.second;
        }
    }
    return -1;
}

int Table::getValue(short_characteristic name) const noexcept{
    for (auto &i: table){
        if (i.first.second == name){
            return i.second;
        }
    }
    return -1;
}

Table& Table::setValue(full_characteristic name, int v){
    if (v < 0){
        throw std::invalid_argument("negative value");
    }
    std::pair<full_characteristic, short_characteristic> tmp;
    if (name == full_characteristic::agility){
        tmp = std::make_pair(full_characteristic::agility, short_characteristic::a);
    } else if (name == full_characteristic::endurance){
        tmp = std::make_pair(full_characteristic::endurance, short_characteristic::e);
    } else if (name == full_characteristic::intelligence){
        tmp = std::make_pair(full_characteristic::intelligence, short_characteristic::i);
    } else if (name == full_characteristic::strength){
        tmp = std::make_pair(full_characteristic::strength, short_characteristic::s);
    }
    table[tmp] = v;

    return *this;
}

Table& Table::setValue(short_characteristic name, int v){
    if (v < 0){
        throw std::invalid_argument("negative value");
    }
    std::pair<full_characteristic, short_characteristic> tmp;
    if (name == short_characteristic::a){
        tmp = std::make_pair(full_characteristic::agility, short_characteristic::a);
    } else if (name == short_characteristic::e){
        tmp = std::make_pair(full_characteristic::endurance, short_characteristic::e);
    } else if (name == short_characteristic::i){
        tmp = std::make_pair(full_characteristic::intelligence, short_characteristic::i);
    } else if (name == short_characteristic::s){
        tmp = std::make_pair(full_characteristic::strength, short_characteristic::s);
    }
    table[tmp] = v;

    return *this;
}


