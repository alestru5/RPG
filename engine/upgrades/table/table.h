#ifndef TABLE_H
#define TABLE_H
#include <map>
#include <iostream>
#include "../../helps/enums.h"


class Table{
    private:
        static const int m_size = 4;
        std::map<std::pair<full_characteristic, short_characteristic>, int> table;
    public:
        Table() noexcept;
        Table(const Table& T) noexcept;

        ~Table() {}

        int getM_Size() const noexcept { return m_size; }
        std::map<std::pair<full_characteristic, short_characteristic>, int> getTable() noexcept { return table; }

        int getValue(full_characteristic name) const noexcept;
        int getValue(short_characteristic name) const noexcept;

        Table& setValue(full_characteristic name, int v);
        Table& setValue(short_characteristic name, int v);

};

#endif // TABLE_H
