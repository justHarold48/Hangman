//
//  Stage.cpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//
#include <Foundation/Foundation.h>

#include "Stage.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <CoreFoundation/CoreFoundation.h>

const std::vector<unsigned> kPos {57, 90, 91, 89, 125, 121};
const std::vector<std::string> kParts {"o", "|", "-", "-", "\\", "/"};

const std::string DUPLICATE_LETTER_EXECEPTION = "Duplicate Letter";
const std::string STAKE_FULL_EXECEPTION = "Stake Complete";
const std::string BASE_FULL_EXCEPTION = "Base Complete";

constexpr uint8_t END_STATE = 5;

void Stage::initStage(const char* word) {
    word_ = std::string(word);
    remaining_ = std::string(word);
    
    stake_ = "     --------------\n"
             "    |                         |\n"
             "                               |\n"
             "                               |\n"
             "                               |\n"
             "                               |\n"
             "                               |\n"
             "                                \n";

    for_each(std::begin(word_), std::end(word_), [&](char c){base_ += "    _";});
}


std::string Stage::getCompleteStage() {
    for(auto letter : remaining_) {
        addLetter(letter);
    }
    
    return (stake_ + base_);
}


bool Stage::makeGuess(char letter) noexcept(false) {
    auto result = false;
    
    if(prevGuessedLetters_.find(letter) != prevGuessedLetters_.end()) {
        throw DUPLICATE_LETTER_EXECEPTION.c_str();
    }

    prevGuessedLetters_.insert(letter);
    
    if(remaining_.find(letter) != std::string::npos) {
        addLetter(letter);
        remaining_.erase(remove(begin(remaining_), end(remaining_), letter), end(remaining_));
        result = true;
    }
    else {
        addBodyPart();
    }
    
    return result;
}


void Stage::addBodyPart() noexcept(false) {
    stake_.replace(kPos[state], kParts[state].length(), kParts[state]);

    if (END_STATE == state++) {
      throw STAKE_FULL_EXECEPTION.c_str();
    }
}


void Stage::addLetter(char letter)
{
    auto new_base = std::string();
    auto space_count = 4;

    // convert char to string
    for(auto c : word_) {
        if(c == letter)
        {
            // add new letter to base
            new_base += "    ";
            new_base += letter;
        }
        else if(base_[space_count] == '_')
        {
            // add empty space
            new_base += "    _";
        }
        else
        {
            // add previously added letter
            new_base += "    ";
            new_base += base_[space_count];
        }

        space_count += 5;
    }

    base_ = new_base ;
}
