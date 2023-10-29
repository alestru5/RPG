#include "table.h"

Table::Table(){
    table[std::make_pair(full_characteristic::maximum_hp, short_characteristic::max_hp)] = 100;
    table[std::make_pair(full_characteristic::current_hp, short_characteristic::cur_hp)] = 100;
    table[std::make_pair(full_characteristic::strength, short_characteristic::s)] = 50;
    table[std::make_pair(full_characteristic::agility, short_characteristic::a)] = 50;
    table[std::make_pair(full_characteristic::endurance, short_characteristic::e)] = 50;
    table[std::make_pair(full_characteristic::intelligence, short_characteristic::i)] = 50;
}
Table::Table(int n, std::map<std::pair<full_characteristic, short_characteristic>, int>t){
    if (n > m_size){
        throw std::invalid_argument("n is bigger than m_size");
    }
    for (auto &i: t){
        if (table.count(i.first) == 0){
            table[i.first] = i.second;
        }
    }
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

Table& Table::setValue(full_characteristic name, int v) noexcept{
    for (auto &i: table){
        if (i.first.first == name){
            table[i.first] = v;
            return *this;
        }
    }
    if (table.size() == m_size){
        throw std::invalid_argument("table is full");
    }
    std::pair<full_characteristic, short_characteristic> tmp;
    switch(name){
    case full_characteristic::maximum_hp: tmp = std::make_pair(full_characteristic::maximum_hp, short_characteristic::max_hp);
        case full_characteristic::current_hp: tmp = std::make_pair(full_characteristic::current_hp, short_characteristic::cur_hp);
        case full_characteristic::strength: tmp = std::make_pair(full_characteristic::strength, short_characteristic::s);
        case full_characteristic::agility: tmp = std::make_pair(full_characteristic::agility, short_characteristic::a);
        case full_characteristic::intelligence: tmp = std::make_pair(full_characteristic::intelligence, short_characteristic::i);
        case full_characteristic::endurance: tmp = std::make_pair(full_characteristic::endurance, short_characteristic::e);
    };
    table[tmp] = v;

    return *this;
}

Table& Table::setValue(short_characteristic name, int v) noexcept{
    for (auto &i: table){
        if (i.first.second== name){
            table[i.first] = v;
            return *this;
        }
    }
    if (table.size() == m_size){
        throw std::invalid_argument("table is full");
    }
    std::pair<full_characteristic, short_characteristic> tmp;
    switch(name){
        case short_characteristic::max_hp: tmp = std::make_pair(full_characteristic::maximum_hp, short_characteristic::max_hp);
        case short_characteristic::cur_hp: tmp = std::make_pair(full_characteristic::current_hp, short_characteristic::cur_hp);
        case short_characteristic::s: tmp = std::make_pair(full_characteristic::strength, short_characteristic::s);
        case short_characteristic::a: tmp = std::make_pair(full_characteristic::agility, short_characteristic::a);
        case short_characteristic::i: tmp = std::make_pair(full_characteristic::intelligence, short_characteristic::i);
        case short_characteristic::e: tmp = std::make_pair(full_characteristic::endurance, short_characteristic::e);
    };
    table[tmp] = v;

    return *this;
}


