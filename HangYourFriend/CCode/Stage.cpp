//
//  Stage.cpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//
#import <Foundation/Foundation.h>
#include "Stage.hpp"
#include <stdio.h>
#include <string>
#include <sstream>
#include <CoreFoundation/CoreFoundation.h>

std::string const DUPLICATE_LETTER_EXECEPTION = "Duplicate Letter";
std::string const STAKE_FULL_EXECEPTION = "Stake Complete";
std::string const BASE_FULL_EXCEPTION = "Base Complete";

Stage::Stage()
{
    state = 1;
    prevGuessList = "";
}


void Stage::initStage(const char* word)
{
    this->word = word;

    stake = "     --------------\n"
    "    |                         |\n"
    "                               |\n"
    "                               |\n"
    "                               |\n"
    "                               |\n"
    "                               |\n"
    "                                \n"; 


    base = "";

    for(int i = 0; i < this->word.length(); i++)
    {
        base += "    _";
    }
}


int Stage::getState()
{
    return state;
}


std::string Stage::getStage()
{
    return (stake + base);
}


std::string Stage::getCompleteStage()
{
    for(char letter : word)
        if(prevGuessList.find(letter) == std::string::npos)
            insertBaseLetter(letter);

    return (stake + base);
}


bool Stage::makeGuess(char letter) noexcept(false)
{
    if(prevGuessList.find(letter) != std::string::npos)
        throw DUPLICATE_LETTER_EXECEPTION.c_str();

    if (word.find(letter) != std::string::npos)
    {
        insertBaseLetter(letter);

        if(base.find("_") == std::string::npos)
            throw BASE_FULL_EXCEPTION.c_str();

        return true;
    }
    else
    {
      prevGuessList += letter;
      addBodyPart();
    }

    return false;
}


void Stage::addBodyPart() noexcept(false)
{
  string head = "o" ;
  string rleg = "\\";
  string arm = "-";
  string torso = "|";
  string lleg = "/";

  int head_pos = 56;
  int torso_pos = 88;
  int rarm_pos = 89;
  int larm_pos = 87;
  int rleg_pos = 121;
  int lleg_pos = 118;

  switch(state++)
  {
  case 1:
    stake.replace(head_pos, head.length()+1, head);
    break;
  case 2:
    stake.replace(torso_pos, torso.length()+1, torso);
    break;
  case 3:
    stake.replace(rarm_pos, arm.length()+1, arm);
    break;
  case 4:
    stake.replace(larm_pos, arm.length(), arm);
    break;
  case 5:
    stake.replace(rleg_pos, rleg.length()+1, rleg);
    break;
  case 6:
    stake.replace(lleg_pos, lleg.length(), lleg);
    throw STAKE_FULL_EXECEPTION.c_str();
  }

}


void Stage::insertBaseLetter(char letter)
{
    prevGuessList += letter;
    std::string newBase = "";
    int baseCount = 4;

    // convert char to string
    for(int i = 0 ; i < word.length(); i++)
    {
        if(word[i] == letter)
        {
            // add new letter to base
            newBase += "    ";
            newBase += letter;

        }else if(base[baseCount] == '_')
        {
            // add empty space
            newBase += "    _";
        }
        else
        {
            // add previously added letter
            newBase += "    ";
            newBase += base[baseCount];
        }

        baseCount += 5;
    }

    base = newBase ;
}
