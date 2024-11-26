//---------------------------------------------------------------------------------------------------------------------
// ItemsList.hpp
//
// The header file contains the ItemsList class, which is used to create all items in the game independently from the
// inventories.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef ITEMSLIST_HPP
#define ITEMSLIST_HPP

#include <map>
#include <vector>
#include <string>

#include "Weapons.hpp"
#include "Potion.hpp"
#include "Ammunition.hpp"
#include "Armor.hpp"

class ItemsList
{
  private:
    Weapon *dagg = new Weapon("DAGG", "Dagger", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::HIT, "1 d4 + VIT", 1, 4);
    Weapon *mace = new Weapon("MACE", "Mace", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::HIT, "1 d6 + STR", 1, 6);
    Weapon *warh = new Weapon("WARH", "Warhammer", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::HIT, "1 d10 + STR", 1, 10);
    Weapon *haxe = new Weapon("HAXE", "Handaxe", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::HIT, "1 d6 + STR", 1, 6);
    Weapon *gaxe = new Weapon("GAXE", "Greataxe", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::SLASH, "1 d12 + STR", 1, 12);
    Weapon *rapi = new Weapon("RAPI", "Rapier", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::THRUST, "1 d8 + VIT", 1, 8);
    Weapon *sswd = new Weapon("SSWD", "Shortsword", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::THRUST, "1 d6 + VIT", 1, 6);
    Weapon *lswd = new Weapon("LSWD", "Longsword", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::SLASH, "1 d10 + STR", 1, 10);
    Weapon *gswd = new Weapon("GSWD", "Greatsword", AttackType::MELEE, DamageType::PHYSICAL,
                              DamagePattern::SLASH, "2 d6 + STR", 2, 6);
    Weapon *sbow = new Weapon("SBOW", "Shortbow", AttackType::RANGED, DamageType::PHYSICAL,
                              DamagePattern::SHOT, "1 d6 + VIT", 1, 6);
    Weapon *lbow = new Weapon("LBOW", "Longbow", AttackType::RANGED, DamageType::PHYSICAL,
                              DamagePattern::SHOT, "1 d8 + VIT", 1, 8);
    Weapon *lcrs = new Weapon("LCRS", "Light Crossbow", AttackType::RANGED, DamageType::PHYSICAL,
                              DamagePattern::SHOT, "1 d8 + VIT", 1, 8);
    Weapon *hcrs = new Weapon("HCRS", "Heavy Crossbow", AttackType::RANGED, DamageType::PHYSICAL,
                              DamagePattern::SHOT, "1 d10 + VIT", 1, 10);

    Weapon *qfir_wiz = new Weapon("QFIR", "Quarterstaff of Fire", AttackType::RANGED,
                                  DamageType::FIRE, DamagePattern::BURST, "3 d6", 3, 6);
    Weapon *qcld_wiz = new Weapon("QCLD", "Quarterstaff of Cold", AttackType::MELEE,
                                  DamageType::COLD, DamagePattern::LINE, "2 d10", 2, 10);
    Weapon *qacd_wiz = new Weapon("QACD", "Quarterstaff of Acid", AttackType::RANGED,
                                  DamageType::ACID, DamagePattern::SHOT, "1 d10", 1, 10);
    Weapon *qfrc_wiz = new Weapon("QFRC", "Quarterstaff of Force", AttackType::MELEE,
                                  DamageType::FORCE, DamagePattern::HIT, "1 d10", 1, 10);

    Weapon *qfir = new Weapon("QFIR", "Quarterstaff of Fire", AttackType::MELEE,
                              DamageType::PHYSICAL, DamagePattern::HIT, "1 d6 + STR", 1, 6);
    Weapon *qcld = new Weapon("QCLD", "Quarterstaff of Cold", AttackType::MELEE,
                              DamageType::PHYSICAL, DamagePattern::HIT, "1 d6 + STR", 1, 6);
    Weapon *qacd = new Weapon("QACD", "Quarterstaff of Acid", AttackType::MELEE,
                              DamageType::PHYSICAL, DamagePattern::HIT, "1 d6 + STR", 1, 6);
    Weapon *qfrc = new Weapon("QFRC", "Quarterstaff of Force", AttackType::MELEE,
                              DamageType::PHYSICAL, DamagePattern::HIT, "1 d6 + STR", 1, 6);

    HealthPotion *nhep = new HealthPotion("NHEP", "Normal Health Potion", "2 d4");
    HealthPotion *ghep = new HealthPotion("GHEP", "Greater Health Potion", "4 d4");
    HealthPotion *shep = new HealthPotion("SHEP", "Superior Health Potion", "8 d4");

    ResistancePotion *firs = new ResistancePotion("FIRS", "Potion of Fire Resistance", DamageType::FIRE);
    ResistancePotion *cors = new ResistancePotion("CORS", "Potion of Cold Resistance", DamageType::COLD);
    ResistancePotion *fors = new ResistancePotion("FORS", "Potion of Force Resistance", DamageType::FORCE);
    ResistancePotion *acrs = new ResistancePotion("ACRS", "Potion of Acid Resistance", DamageType::ACID);

    Ammunition *arrw = new Ammunition("ARRW", "Arrow", sbow, lbow);
    Ammunition *bolt = new Ammunition("BOLT", "Bolt", lcrs, hcrs);

    Armor *larm = new Armor("LARM", "Leather Armor", "1 + VIT");
    Armor *bplt = new Armor("BPLT", "Breastplate", "4 + min(VIT, 2)");
    Armor *chml = new Armor("CHML", "Chain Mail", "6");
    Armor *parm = new Armor("PARM", "Plate Armor", "8");

    std::vector<Weapon *> base_weapons_ = {dagg, mace, warh, haxe, gaxe, rapi, sswd, lswd, gswd,
                                          sbow, lbow, lcrs, hcrs};
    std::vector<Weapon *> staff_weapons_ = {qfir, qcld, qacd, qfrc};
    std::vector<Weapon *> staff_weapons_wiz_ = {qfir_wiz, qcld_wiz, qacd_wiz, qfrc_wiz};
    std::vector<HealthPotion *> health_potions_ = {nhep, ghep, shep};
    std::vector<ResistancePotion *> resist_potions_ = {firs, cors, fors, acrs};
    std::vector<Ammunition *> ammunition_items_ = {arrw, bolt};
    std::vector<Armor *> armor_items_ = {larm, bplt, chml, parm};

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for the Items List which is set to default. All items are generated as private
    /// memebers.
    ///
    /// @param -
    /// @return -
    //
    ItemsList() = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is set to default.
    ///
    /// @param ItemsList&: reference to the ItemsList object
    ///
    /// @return -
    //
    ItemsList(const ItemsList &) = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a destructor for the items list. In it, all items are deleted.
    ///
    /// @param -
    /// @return -
    //
    ~ItemsList();
    //------------------------------------------------------------------------------------------------------------------
    /// This function checks if the string is an item or not.
    ///
    /// @param item: 4-char abbreviation of the item
    ///
    /// @return true if it is an item
    /// @return false if it is not an item
    //
    bool isConsumable(std::string item);
    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the Weapon pointer of a weapon with regards to if the user is a wizard/lich or not.
    ///
    /// @param item: 4-char abbreviation of the item
    /// @param is_wiz: bool if the user is wizard/lich or not
    ///
    /// @return pointer to the weapon
    //
    Weapon *getWeaponItemPtr(std::string item, bool is_wiz);
    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the HealthPotion pointer of a health potion with a specific abbreviation.
    ///
    /// @param item: 4-char abbreviation of the item
    ///
    /// @return pointer to the potion
    //
    HealthPotion *getHealthPotionItemPtr(std::string item);  
    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the ResistancePotion pointer of a resistance potion with a specific abbreviation.
    ///
    /// @param item: 4-char abbreviation of the item
    ///
    /// @return pointer to the potion
    //
    ResistancePotion *getResistPotionItemPtr(std::string item);
    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the Ammunition pointer of an Ammunition with a specific abbreviation.
    ///
    /// @param item: 4-char abbreviation of the item
    ///
    /// @return pointer to the ammo
    //
    Ammunition *getAmmunitionItemPtr(std::string item);
    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the Armor pointer of an Armor with a specific abbreviation.
    ///
    /// @param item: 4-char abbreviation of the item
    ///
    /// @return pointer to the armor
    //
    Armor *getArmorItemPtr(std::string item);
};

#endif