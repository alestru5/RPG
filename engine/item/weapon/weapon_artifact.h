#ifndef WEAPON_ARTIFACT_H
#define WEAPON_ARTIFACT_H

#include "weapon.h"
#include "../../upgrades/artifact/artifact.h"
/*!
 * @brief Класс оружия-артифакта
 */
class WeaponArtifact: public virtual Weapon, public Artifact{
    protected:
        int bonus_damage;
    public:
        /*!
         * @brief Пустой конструктор
         */
        WeaponArtifact() noexcept: Artifact(), Weapon(), bonus_damage(0) { item_type = "weapon_artifact"; }
        WeaponArtifact(std::string wn, int mn, int mx, int bd, std::string at, std::list<std::pair<std::string, int>> c) noexcept:
            Weapon(wn, mn, mx), bonus_damage(bd), Artifact(at, c) { item_type = "weapon_artifact"; }
        /*!
         * @brief Виртуальнйы метод - взять оружие в руки
         * @param Карта
         */
        std::string getItemType() const noexcept override { return item_type; }
        std::string getItemName() const noexcept override { return weapon_name; }
        int getValue() const noexcept override;
        void use(Dungeon &dungeon) override;
        Item* buildItem(const json& data) override;

};

extern "C" Item* load_weapon_artifact();

#endif // WEAPONARTIFACT_H
