//---------------------------------------------------------------------------------------------------------------------
// Potion.hpp
//
// The header file contains multiple classes; the health potion class and the resistance potion class. Both are derived
// from items.
// Health potions regenerate a certain amount of health in a character, while resistance potions make the user
// resistant to one specific damage type (i.e. acid).
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef POTION_HPP
#define POTION_HPP

#include <map>
#include <vector>
#include <string>

#include "Items.hpp"
#include "Weapons.hpp"
#include "Random.hpp"
class HealthPotion : public Items
{
private:
  std::string regenerated_health_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a HealthPotion. 
    ///
    /// @param abbreviation: 4-char abbreviation of the potion
    /// @param name: full name of the potion
    /// @param regenerated_health: max. amount of player health that can be regenerated on use of potion
    ///
    /// @return -
    // 
    HealthPotion(std::string abbreviation, std::string name, std::string regenerated_health);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted. 
    ///
    /// @param HealthPotion&: reference to the HealthPotion object 
    /// 
    /// @return -
    //   
    HealthPotion(const HealthPotion&) = delete;
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //  
    ~HealthPotion() = default; 
    /// This function counts how much health should be regenerated based on potion name;
    ///
    /// @param game: pointer to the game class
    /// 
    /// @return helth that was regenerated
    //  
    int countRegeneration();
};

class ResistancePotion : public Items
{
private:
  DamageType resistance_to_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for a ResistancePotion. 
    ///
    /// @param abbreviation: 4-char abbreviation of the potion
    /// @param name: full name of the potion
    /// @param resistance_to: dmg type the potion makes resistant to upon use (i.e. acid)
    ///
    /// @return -
    // 
    ResistancePotion(std::string abbreviation, std::string name, DamageType resistance_to);
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explictely deleted. 
    ///
    /// @param ResistancePotion&: reference to the ResistancePotion object 
    /// 
    /// @return -
    //   
    ResistancePotion(const ResistancePotion&) = delete;
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //  
    ~ResistancePotion() = default; 
    /// This function gets the name and type of resistance
    ///
    /// @param damage_name: reference to a string to store the resulted name
    /// @param damage_type: reference to a DamageType variable to store the result
    /// @param
    ///
    /// @return -
    //
    void getResistance(std::string &damage_name, DamageType &damage_type);
};

#endif