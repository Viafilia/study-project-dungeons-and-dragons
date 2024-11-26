//---------------------------------------------------------------------------------------------------------------------
// Story.cpp
//
// This is the source file for the Story class.
//
// Group: 090
//
// Author: Maryia Filipovich, 12328063
//---------------------------------------------------------------------------------------------------------------------
//

#include "Story.hpp"
#include <string>
#include <fstream>
#include <iostream>

Story::Story(char* config_path)
{
  std::ifstream fin(config_path);
  std::string line;
  std::getline(fin, line);
  while (std::getline(fin, line))
  {
    int pos = line.find(':');
    std::string key = line.substr(0, pos);
    line.erase(0, pos + 1);
    for (unsigned int i = 0; i < line.size(); i++)
    {
      if (line[i] == ';')
        line[i] = '\n';
    }
    if (line[0] != '\n')
    {
      if (key[0] == 'N')
      {
        line.insert(0, "** ");
      }
      else
      {
        line.insert(0, "!! ");
      }
    }
    for (unsigned int i = 0; i < line.size() - 1; i++)
    {
      if (line[i] == '\n' && line[i + 1] != '\n')
      {
        if (key[0] == 'N')
        {
          line.insert(i + 1, "** ");
        }
        else
        {
          line.insert(i + 1, "!! ");
        }
      }
    }
    story_[key] = line;
  }
}

void Story::printStory(std::string key_value)
{
  std::cout << story_[key_value];
}