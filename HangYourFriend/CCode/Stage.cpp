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

int const COMPLETE_STATE = 6;

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
    stake = getStakeState(state);
    base = "";

    for(int i = 0; i < this->word.length(); i++)
    {
        base += "    _";
    }
}


void Stage::nextStageState() noexcept(false)
{
    state++;
    
    if (state == COMPLETE_STATE)
    {
        stake = getStakeState(state);
        throw STAKE_FULL_EXECEPTION.c_str();
    }
    
    stake = getStakeState(state);
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

    prevGuessList += letter;
    nextStageState();

    return false;
}


std::string Stage::getStakeState(int state)
{
    switch(state)
    {
        case 0:
            return  "     --------------\n"
                    "    |                         |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 1:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 2:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "    |                         |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 3:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "    |-                       |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 4:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "   -|-                      |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 5:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "   -|-                      |\n"
                    "      \\                       |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        case 6:
            return  "     --------------\n"
                    "    |                         |\n"
                    "   O                        |\n"
                    "   -|-                      |\n"
                    "    / \\                       |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
        default:
            return  "     --------------\n"
                    "    |                         |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                               |\n"
                    "                                \n";
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
