
//---------------------------------------------------------------------------------------------------------------------
//
// this is a header file for armor, that stores its information and properties
//
// Group: 090
//
// Author: Sarah Pennauer
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <map>
#include <vector>
#include <string>

#include "Items.hpp"

class Armor : public Items
{
  private:
    std::string armor_value_;

  public:
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for an Armor object.
    ///
    /// @param abbreviation: abbreviation of the armor object
    /// @param name: the full name of the armor object
    /// @param armor_value: value in for of a string that gived information about its properties
    ///
    /// @return -
    //
    Armor(std::string abbreviation, std::string name, std::string armor_value)
    {
      abbreviation_ = abbreviation;
      name_ = name;
      armor_value_ = armor_value;
    }
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is explicitely deleted.
    ///
    /// @param Armor&: reference to the Armor object
    ///
    /// @return -
    //
    Armor(const Armor &) = delete;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a virutal default destructor of an Armor
    ///
    /// @param -
    ///
    /// @return -
    //
    ~Armor() = default;
};

#endif