//---------------------------------------------------------------------------------------------------------------------
// Character.hpp
//
// This is a header file for the character class, which is derived from the entity class.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254, Maryia Filipovich 12328063
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <vector>
#include <utility>
#include "Entity.hpp"
#include "Weapons.hpp"

enum class CharacterType
{
  PLAYER,
  ROGUE,
  BARBARIAN,
  WIZARD,
  ENEMY,
  LICH,
  GOBLIN,
  ZOMBIE,
  CHEST
};

class Character : public Entity
{
  protected:
    int health_;
    int vitality_;
    int strength_;
    int max_health_;
    int armour_value_;
    DamageType resistance_ = DamageType::NONE;
    std::string abbreviation_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor is set to default.
    //
    Character() = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// We do not allow initializing one character object to another one.
    //
    Character(const Character &) = delete;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor is set to default.
    //
    ~Character() = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// virtual method that reduces character's health based on damage type, damage amount
    /// and personal characteristics of a character
    ///
    ///
    /// @param type type of damage that is caused by a weapon
    /// @param damage amount of damage that weapon gives
    //
    void getDamage(DamageType type, int damage) override;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// gets name of character
    ///
    ///
    /// @return name of character
    //
    virtual std::string getName() = 0;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// calculates armor value of a character based on its type and equiped armor
    ///
    ///
    /// @return armor value
    //
    virtual int calcArmor() = 0;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// gets virality of character
    ///
    ///
    /// @return vitality of character
    //
    int getVitality();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// gets strength of character
    ///
    ///
    /// @return strength of character
    //
    int getStrength();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// makes character dead
    ///
    ///
    //
    virtual void die() {};
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// gets type of character
    ///
    ///
    /// @return type of character
    //
    virtual EntityType getEntityType() override = 0;
};

#endif