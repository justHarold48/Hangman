//
//  Stage.cpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//
#include <Foundation/Foundation.h>

#include "Stage.hpp"
#include <stdio.h>
#include <string>
#include <sstream>
#include <CoreFoundation/CoreFoundation.h>

using namespace std;

const unsigned int POS [] = {57, 90, 91, 89, 125, 121};

const std::string PARTS [] = {"o", "|", "-", "-", "\\", "/"};

const std::string DUPLICATE_LETTER_EXECEPTION = "Duplicate Letter";
const std::string STAKE_FULL_EXECEPTION = "Stake Complete";
const std::string BASE_FULL_EXCEPTION = "Base Complete";

constexpr uint8_t END_STATE = 5;

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

    for(int i = 0; i < std::strlen( word ); i++)
        base += "    _";

}


unsigned int Stage::getState()
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
            insertLetter(letter);

    return (stake + base);
}


bool Stage::makeGuess(const char& letter) noexcept(false)
{
    if(prevGuessList.find(letter) != std::string::npos)
        throw DUPLICATE_LETTER_EXECEPTION.c_str();

    if (word.find(letter) != std::string::npos)
    {
        insertLetter(letter);

        if(base.find("_") == std::string::npos)
            throw BASE_FULL_EXCEPTION.c_str();

        return true;
    }

    prevGuessList += letter;
    addBodyPart();

    return false;
}


void Stage::addBodyPart() noexcept(false)
{
  stake.replace(POS[state], PARTS[state].length(), PARTS[state]);

  if (END_STATE == state++)
    throw STAKE_FULL_EXECEPTION.c_str();
}


void Stage::insertLetter(const char& letter)
{
    prevGuessList += letter;
    string newBase = "";
    int spaceCount = 4;

    // convert char to string
    for(size_t i = 0 ; i < word.length(); i++)
    {
        if(word[i] == letter)
        {
            // add new letter to base
            newBase += "    ";
            newBase += letter;

        }
                   else if(base[spaceCount] == '_')
        {
            // add empty space
            newBase += "    _";
        }
        else
        {
            // add previously added letter
            newBase += "    ";
            newBase += base[spaceCount];
        }

        spaceCount += 5;
    }

    base = newBase ;
}
