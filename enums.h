#ifndef ENUMS_H
#define ENUMS_H

enum class name_weapon{
    knife,
    sword,
    nunchucks
};

enum class type_artifact{
    casual,
    rare,
    mythical,
    legendary,
};

enum class full_characteristic{
    maximum_hp,
    current_hp,
    strength,
    agility,
    intelligence,
    endurance
};

enum class short_characteristic{
    max_hp,
    cur_hp,
    s,
    a,
    i,
    e
};

enum class type_item{
    equipment,
    equipment_artifact,
    weapon,
    weapon_artifact,
    weapon_enchantment,
    weapon_artifact_enchantment,
    potion,
    bunch
};

enum class name_potion{
    experience,
    hp,
    strength,
    agility,
    intelligence
};

enum class changes_characteristic{
    experience,
    hp,
    strength,
    agility,
    intelligence,
};

enum class type_enchantment{
    WhiteKiller,
    RedKiller,
    BlackKiller,
    BlueKiller
};

enum class trait{
    white,
    red,
    black,
    blue
};

enum class name_equipment{
    leather,
    iron,
    gold,
    diamond
};

enum class type_equipment{
    helmet,
    bib,
    leggings,
    boots
};

enum class type_bunch{
    big,
    medium,
    small
};

enum class type_cell{
    floor,
    open_door,
    close_door,
    up_ladder,
    down_ladder,
    wall,
};

enum class name_enemy{
    white_golem,
    black_druid,
    red_tiger,
    blue_wolf
};


#endif // ENUMS_H
