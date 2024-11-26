//---------------------------------------------------------------------------------------------------------------------
// Items.hpp
//
// The header file contains the Items class, which is used as a base class for all items.
//
// Group: 090
//
// Author: Julia Jesenko
//---------------------------------------------------------------------------------------------------------------------
//

#ifndef ITEMS_HPP
#define ITEMS_HPP

#include <string>
#include <iostream>

class Items
{
  protected:
    std::string abbreviation_;
    std::string name_;

  public: 
    //------------------------------------------------------------------------------------------------------------------
    /// This function is a constructor for Items which is set to default
    ///
    /// @param -
    ///
    /// @return -
    //
    Items() = default;
    //------------------------------------------------------------------------------------------------------------------
    /// This function is the copy constructor which is deleted explicitely. 
    ///
    /// @param Items&: reference to the Items object 
    /// 
    /// @return -
    //    
    Items(const Items&) = delete;
    /// This function is the destructor which is set to default. 
    ///
    /// @param -
    /// 
    /// @return -
    //  
    virtual ~Items() = default;
    /// This function returns the item's abbreviation as a string. 
    ///
    /// @param -
    /// 
    /// @return the abbreviation of the item
    //  
    virtual std::string& getAbbreviation()
    {
      return abbreviation_;
    }    
    /// This function returns the item's name as a string. 
    ///
    /// @param -
    /// 
    /// @return the name of the item
    //  
    std::string& getName()
    {
      return name_;
    }
};

#endif
