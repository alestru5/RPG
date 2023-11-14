#include "setchanges.h"

std::list<std::pair<short_characteristic, int>> SetChanges::createChanges(type_artifact T){
    std::list<std::pair<short_characteristic, int>> changes;
        if (T == type_artifact::casual){
        changes.push_back(std::make_pair(short_characteristic::e, 5));
        changes.push_back(std::make_pair(short_characteristic::a, 5));
        changes.push_back(std::make_pair(short_characteristic::i, 5));
        changes.push_back(std::make_pair(short_characteristic::s, 5));
        return changes;
    } else if (T == type_artifact::rare){
        changes.push_back(std::make_pair(short_characteristic::e, 10));
        changes.push_back(std::make_pair(short_characteristic::a, 10));
        changes.push_back(std::make_pair(short_characteristic::i, 10));
        changes.push_back(std::make_pair(short_characteristic::s, 10));
        return changes;
    } else if (T == type_artifact::mythical){
        changes.push_back(std::make_pair(short_characteristic::e, 15));
        changes.push_back(std::make_pair(short_characteristic::a, 15));
        changes.push_back(std::make_pair(short_characteristic::i, 15));
        changes.push_back(std::make_pair(short_characteristic::s, 15));
        return changes;
    } else if (T == type_artifact::legendary){
        changes.push_back(std::make_pair(short_characteristic::e, 25));
        changes.push_back(std::make_pair(short_characteristic::a, 25));
        changes.push_back(std::make_pair(short_characteristic::i, 25));
        changes.push_back(std::make_pair(short_characteristic::s, 25));
        return changes;
    } else {
        throw std::invalid_argument("its not artifact");
    }
}


