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

std::string const parts [] = {"o", "|", "-", "-", "\\", "/"};
int const pos [] = {57, 90, 91, 89, 125, 121};

std::string const DUPLICATE_LETTER_EXECEPTION = "Duplicate Letter";
std::string const STAKE_FULL_EXECEPTION = "Stake Complete";
std::string const BASE_FULL_EXCEPTION = "Base Complete";

Stage::Stage()
{
    state = 0;
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
  stake.replace(pos[state], parts[state].length(), parts[state]);

  if (5 == state++)
    throw STAKE_FULL_EXECEPTION.c_str();
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
