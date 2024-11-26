//---------------------------------------------------------------------------------------------------------------------
// Weapons.hpp
//
// The header file contains multiple classes; the weapons class which is derived from the items class and multiple
// enum classes, that are used to define weapons
//    enum class AttackType: range of a weapon: i.e. ranged
//    enum class DamageType: type of damage of a weapon: i.e. acid - this is what potions can make resistant to
//    enum class DamagePattern: fields that are hit by an attack of that weapon: i.e. hit
// The Weapons class collects the enum class "properties" of a weapon and also stores the damage amount (i.e. 1 d4 +
// VIT) and from that the number of dices and the dice type.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef WEAPONS_HPP
#define WEAPONS_HPP

#include <map>
#include <vector>
#include <string>

#include "Items.hpp"

enum class AttackType
{
  MELEE,
  RANGED
};

enum class DamageType
{
  NONE,
  PHYSICAL,
  FIRE,
  COLD,
  ACID,
  FORCE
};

enum class DamagePattern
{
  HIT,
  SLASH,
  THRUST,
  SHOT,
  BURST,
  LINE
};

class Weapon : public Items
{
private:
  AttackType attack_type_;
  DamageType damage_type_;
  DamagePattern damage_pattern_;
  std::string damage_amount_;
  int roll_amount_;
  int dice_type_;

public:
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a constructor for a Weapon.
  ///
  /// @param weapon_abbrev: 4-char abbreviation of the weapon
  /// @param name: full name of the weapon
  /// @param attack_type: AttackType of the weapon -> see enum class AttackType (defines reach of a weapon)
  /// @param damage_type: DamageType of the weapon -> see enum class DamageType (defines type of dmg, i.e. acid)
  /// @param damage_pattern: DamagePattern of the weapon -> see enum class DamagePattern (defines which fields are hit
  ///                        by a weapon attack)
  /// @param damage_amount: how much dmg the weapon does in its base form
  /// @param roll_amount: how often the dice is rolled when the weapon is used
  /// @param dice_type: the dice type that is rolled when the weapon is used
  ///
  /// @return -
  //
  Weapon(std::string weapon_abbrev, std::string name, AttackType attack_type, DamageType damage_type,
         DamagePattern damage_pattern, std::string damage_amount, int roll_amount, int dice_type);
  //------------------------------------------------------------------------------------------------------------------
  /// This function is the copy constructor which is explicitely deleted.
  ///
  /// @param Weapon&: reference to the Weapon object
  ///
  /// @return -
  //
  Weapon(const Weapon &) = delete;
  /// This function is the destructor which is set to default.
  ///
  /// @param -
  ///
  /// @return -
  //
  ~Weapon() = default;
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a Getter-Method for the weapon's attack-type.
  ///
  /// @param -
  /// @return weapon's attack type
  //
  AttackType getAttackType();
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a Getter-Method for the weapon's damage-type.
  ///
  /// @param -
  /// @return weapon's damage type
  //
  DamageType getDamageType();
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a Getter-Method for the weapon's damage-pattern.
  ///
  /// @param -
  /// @return weapon's damage pattern
  //
  DamagePattern getDamagePattern();
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a Getter-Method for the weapon's dice type.
  ///
  /// @param -
  /// @return weapon's dice type
  //
  int getDiceType();
  //------------------------------------------------------------------------------------------------------------------
  /// This function is a Getter-Method for the weapon's roll amount.
  ///
  /// @param -
  /// @return weapon's roll amount
  //
  int getRollAmount();
};

#endif