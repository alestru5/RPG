#include "setpotion.h"

std::pair<changes_characteristic, int> SetPotion::createChanges(name_potion N){
    std::pair<changes_characteristic, int> changes;
    if (N == name_potion::experience){
        changes = (std::make_pair(changes_characteristic::experience, 100));
    } else if (N == name_potion::hp){
        changes = (std::make_pair(changes_characteristic::hp, 100));
    } else if (N == name_potion::agility){
        changes= (std::make_pair(changes_characteristic::agility, 5));
    } else if (N == name_potion::intelligence){
        changes= (std::make_pair(changes_characteristic::intelligence, 5));
    } else if (N == name_potion::strength){
        changes = (std::make_pair(changes_characteristic::strength, 5));
    } else if (N == name_potion::endurance){
        changes = (std::make_pair(changes_characteristic::endurance, 5));
    }
    return changes;
}
