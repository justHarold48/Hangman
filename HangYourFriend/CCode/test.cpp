//
//  Stage.cpp
//  HangYourFriend
//
//  Created by Harold Hatch on 10/8/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#include <stdio.h>
#include "Header.h"


Stage::Stage(int length)
{
    state = length;
    /*
    state = 0;
    
    stake = "   --------------\n"
            "   |            |\n"
            "                |\n"
            "                |\n"
            "                |\n"
            "                |\n"
            "                |\n"
            "                 \n";
    
    base = " ";
    
    for(int i = 0; i < length; ++i)
        base += " _ ";
    
    base += "\n";
     */
}

int Stage::getState() const
{
    //char* value = strdup((stake + base).c_str());
    return state;
}
/*
void Stage::addLetter(int indexs [], string letter )
{
    string newBase = " ";
    int baseCount = 2;
    string charac = 0;
    bool contains = false;
    
    int length = sizeof(indexs)/sizeof(indexs[0]);
    
    for(int i = 0; i < (base.length()/3); i++)
    {
        for(int n = 0; n < length; n++)
            if(indexs[n] == i)
                contains = true;
        
        charac = base.at(baseCount);
        
        if (contains)
            newBase += " " + letter + " ";
        else if (charac == "_")
            newBase += " _ ";
        else
            newBase += " " + charac + " ";
        
        baseCount += 3;
        contains = false;
    }
    
    newBase += "\n";
    base = newBase;
    
    if(!newBase.find("_"))
        throw "Error!! Base Complete";
}
*/
void Stage::addBodyPart()
{
    state++;
    /*
    switch(state)
    {
        case 1:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "                |\n"
             "                |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            break;
        case 2:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "   |            |\n"
             "                |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            break;
        case 3:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "   |-           |\n"
             "                |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            break;
        case 4:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "  -|-           |\n"
             "                |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            break;
        case 5:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "  -|-           |\n"
             "    \\           |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            break;
        case 6:
            stake = "   --------------\n"
             "   |            |\n"
             "   O            |\n"
             "  -|-           |\n"
             "  / \\           |\n"
             "                |\n"
             "                |\n"
             "                 \n";
            throw "Error!! Stake Complete";
            break;
    }
    */
}

Stage::~Stage()
{
    
}

