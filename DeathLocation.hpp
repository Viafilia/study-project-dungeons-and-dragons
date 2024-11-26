//---------------------------------------------------------------------------------------------------------------------
// DeathLocation.hpp
//
// The header file contains the DeathLocation class, which is derived from Entity. A Death Location serves to store
// the loot of a character upon their death and can be looted.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef DEATHLOCATION_HPP
#define DEATHLOCATION_HPP

#include <vector>
#include <utility>

#include "Inventory.hpp"
#include "Entity.hpp"

class DeathLocation : public Entity
{
  private:
    Inventory *death_location_loot_;
    bool is_looted_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a Death Location.
    /// In this constructor, the Death Location copies the dead entity's inventory.
    ///
    /// @param dead_entity_inventory: pointer to the inventory of the deceased entity for copying
    /// @return -
    //
    DeathLocation(Inventory *dead_entity_inventory);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is set to default.
    ///
    /// @param DeathLocation&: reference to the Weapon object
    ///
    /// @return -
    //
    DeathLocation(const DeathLocation &) = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a destructor for a Death Location.
    /// In this destructor, the created loot (inventory) is deleted.
    ///
    /// @param -
    /// @return -
    //
    ~DeathLocation();

    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Getter-Method for the death location contents.
    ///
    /// @param -
    /// @return pointer to the treasure chest inventory
    //
    Inventory *getDeathLocationLoot();
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a Setter-Method for the death location's loot-status, setting it to has-been-looted.
    ///
    /// @param -
    /// @return
    //
    void setDeathLocationLootTrue();

    //------------------------------------------------------------------------------------------------------------------
    /// This function returns the Entity Type Death Location.
    ///
    /// @param -
    /// @return
    //
    EntityType getEntityType() override;
    //------------------------------------------------------------------------------------------------------------------
    /// This function prints the Death Location's abbreviation.
    ///
    /// @param -
    /// @return
    //
    void print() const override;
};

#endif