#ifndef TABLE_H
#define TABLE_H

#include <map>
#include <iostream>

#include "../../../json.hpp"
using json = nlohmann::json;

class Table{
    private:
        static const int m_size = 4;
        std::map<std::pair<std::string, std::string>, int> table;
    public:
        Table() noexcept;
        Table(const Table& T) noexcept;

        ~Table() {}

        int getM_Size() const noexcept { return m_size; }
        std::map<std::pair<std::string, std::string>, int> getTable() noexcept { return table; }

        int getValue(std::string name) const noexcept;

        Table& setValue(std::string name, int v);

        Table& buildTable(const json& data) {}
};

#endif // TABLE_H
