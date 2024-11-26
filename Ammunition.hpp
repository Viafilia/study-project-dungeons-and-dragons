
//---------------------------------------------------------------------------------------------------------------------
// Ammunition.hpp
// The header file for the ammunition class, which is derived from the items class, storing the information and
// properties of the class.
//
// Group: 090
//
// Author: Sarah Pennauer, 01331166
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef AMMUNITION_HPP
#define AMMUNITION_HPP

#include <map>
#include <vector>
#include <string>

#include "Items.hpp"
#include "Weapons.hpp"

class Ammunition : public Items
{
  private: 
    Weapon* used_for_w1_;
    Weapon* used_for_w2_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for an Ammunition object. 
    ///
    /// @param abbreviation: abbreviation of the ammunition object
    /// @param name: the full name of the ammunition object
    /// @param weapon_one: the first weapon the ammunition is used for
    /// @param weapon_two: the second weapon the ammunition is used for
    ///
    /// @return -
    //
    Ammunition(std::string abbreviation, std::string name, Weapon *weapon_one, Weapon *weapon_two)
    {
      abbreviation_ = abbreviation;
      name_ = name;
      used_for_w1_ = weapon_one;
      used_for_w2_ = weapon_two;
    }
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted. 
    ///
    /// @param Ammunition&: reference to the Ammunition object 
    /// 
    /// @return -
    //   
    Ammunition(const Ammunition&) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //   
    ~Ammunition() = default; 
};

#endif