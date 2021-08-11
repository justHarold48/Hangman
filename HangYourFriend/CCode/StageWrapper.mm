//
//  StageWrapper.m
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#include "StageWrapper.h"
#include "Stage.hpp"

#include <iostream>

@interface StageWrapper()
{
    Stage stage;
}

@end

@implementation StageWrapper

-(void)initStage:(const char*)word
{
    stage.initStage(word);
}

-(void)addBodyPart
{
    try
    {
        stage.addBodyPart();
    }
    catch (const char* e)
    {
        std::cout << "\nC++ Error Occured.. Caught in OBJC.. Thrown to Swift: " << std::endl;
        std::cout << e << std::endl;
        std::cout << "\n" << std::endl;

        NSString* reason = [NSString stringWithUTF8String:e];
        NSString* name = reason;

        NSException *exception = [NSException
                                  exceptionWithName:name
                                  reason: reason
                                  userInfo:nil];
        @throw exception;
    }
}

-(int)getState
{
    return stage.getState();
}

- (NSString*)getStage
{
    return [NSString stringWithUTF8String:stage.getStage().c_str()];
}

- (NSString*)getRemainingLetters
{
    return [NSString stringWithUTF8String:stage.getRemainingLetters().c_str()];
}

- (NSString*)getCompleteStage
{
    return [NSString stringWithUTF8String:stage.getCompleteStage().c_str()];
}

- (bool)makeGuess:(char)letter
{
    auto result = false;
    
    try {
        result = stage.makeGuess(letter);

    } 
    catch (const char* e) {
        std::cout << "\nC++ Error Occured.. Caught in OBJC.. Thrown to Swift: " << std::endl;
        std::cout << e << std::endl;
        std::cout << "\n" << std::endl;

        NSString* reason = [NSString stringWithUTF8String:e];
        NSString* name = reason;

        NSException *exception = [NSException
                          exceptionWithName:name
                          reason: reason
                          userInfo:nil];
        @throw exception;
    }
    
    return result;
}

- (BOOL)catchException:(void(^)())tryBlock error:(__autoreleasing NSError **)error {
    @try {
        tryBlock();
        return YES;
    }
    @catch (NSException *exception) {
        *error = [[NSError alloc] initWithDomain:exception.name code:0 userInfo:exception.userInfo];
        return NO;
    }
}

@end
