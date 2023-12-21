#ifndef EQUIPMENT_ARTIFACT_H
#define EQUIPMENT_ARTIFACT_H

#include "equipment.h"
/*!
 * @brief Класс брони-артифакта
 */
class EquipmentArtifact: public Equipment, public Artifact{
    private:
        // Бонусная броня
        int bonus_protect;

    public:
        /*!
         * @brief Пустой конструктор
         */
        EquipmentArtifact() noexcept: Equipment(), Artifact(), bonus_protect(0) { item_type = "equipment_artifact"; }
        EquipmentArtifact(std::string en, std::string et, int mn, int mx, int bp,
                          std::string at, std::list<std::pair<std::string, int>> c) noexcept:
                Equipment(en, et, mn, mx), Artifact(at, c), bonus_protect(bp) {item_type = "equipment_artifact";}
        /*!
         * @brief Оператор копирования
         * @param I Другая броня
         * @return Ссылка на текущую броню
         */
        EquipmentArtifact& operator=(const EquipmentArtifact& I) noexcept;

        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return equipment_name + "_" + equipment_type + "_" + artifact_type; }
        int getValue() const noexcept override;
        void use(Dungeon &dungeon) override;
        Item* buildItem(const json& data) override;
};

extern "C" Item* load_equipment_artifact();


#endif // EQUIPMENTARTIFACT_H
