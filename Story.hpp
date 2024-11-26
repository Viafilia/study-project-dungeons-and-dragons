//---------------------------------------------------------------------------------------------------------------------
//
// this is a header file for the story, that stores stories storys by their keys and parses the story config
//
// Group: 090
//
// Author: Maryia FIlipovich, 12328063
//---------------------------------------------------------------------------------------------------------------------
//
#ifndef STORY_HPP
#define STORY_HPP

#include <string>
#include <map>

class Story
{
private:
  std::map <std::string, std::string> story_;
public:
//--------------------------------------------------------------------------------------------------------------------
  ///
  /// this is a constructor for story class, which parses a story config
  ///
  /// @param config_path path to the config file
  ///
  /// @return story
  //
  Story(char* config_path);
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// copy constructor is deleted as it isnt needed
  //
  Story(const Story&) = delete;
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// default destructor
  //
  ~Story() = default;
  //--------------------------------------------------------------------------------------------------------------------
  ///
  /// this function prints needed story be given key
  ///
  /// @param key_value name of the story-key
  ///
  /// @return -
  //
  void printStory(std::string key_value);
};

#endif