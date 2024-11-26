//---------------------------------------------------------------------------------------------------------------------
// Entity.hpp
//
// This is a header file for the entity class, which is the parent class for all the other subgroups, like e.g door.
//
// Group: 090
//
// Author: Julia Jesenko, 12312254
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <vector>
#include <utility>
#include "Items.hpp"
#include <iostream>
#include "Weapons.hpp"

enum class EntityType
{
  DEATH_LOCATION,
  CHEST, 
  PLAYER,
  ENEMY,
  ENTITY
};

class Entity
{
  protected:
  std::string abbreviation_;
  std::pair<int,int> position_;
  bool is_alive_;

  public:
    //void printItems();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The constructor of the entity class, sets the alive status to true.
    ///
    /// @param nothing
    //
    Entity();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The copy constructor is set to default.
    //
    Entity(const Entity& e) = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The destructor is set to default.
    //
    virtual ~Entity() = default;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// The get damage function.
    ///
    /// @param type the type of damage
    /// @param damage the damage amount
    //
    virtual void getDamage(DamageType type, int damage);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Standard print function
    ///
    /// @param -
    ///
    /// @return -
    //
    virtual void print() const;
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the position member.
    ///
    /// @param -
    ///
    /// @return the position member
    //
    virtual std::pair<int,int> getPosition();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the abbreviation member.
    ///
    /// @param -
    ///
    /// @return the abbreviation member
    //
    virtual std::string getAbbrev();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Setter for the abbreviation member.
    ///
    /// @param -
    ///
    /// @return -
    //
    void setPosition(int row, int col);
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the is_alive member.
    ///
    /// @param -
    ///
    /// @return the is_alive member
    //
    bool getAliveStatus();
    //------------------------------------------------------------------------------------------------------------------
    ///
    /// Getter for the entity type member.
    ///
    /// @param -
    ///
    /// @return the the entity type entity
    //
    virtual EntityType getEntityType();
};

#endif