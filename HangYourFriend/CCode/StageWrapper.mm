//
//  StageWrapper.m
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#import "StageWrapper.h"
#include "Stage.hpp"

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

-(void)nextStageState
{
    try
    {
        stage.nextStageState();
    }
    catch (const char* e)
    {
        
        printf("\nC++ Error Occured.. Caught in OBJC.. Thrown to Swift: ");
        printf("%s", e);
        printf("\n\n");
        
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
    NSString* nsStage = [NSString stringWithUTF8String:stage.getStage().c_str()];
    return nsStage;
}

- (NSString*)getCompleteStage
{
    NSString* nsStage = [NSString stringWithUTF8String:stage.getCompleteStage().c_str()];
    return nsStage;
}

- (bool)makeGuess:(char)letter
{
    try
    {
        return stage.makeGuess(letter);
        
    } catch (const char* e)
    {

        printf("\nC++ Error Occured.. Caught in OBJC.. Thrown to Swift: ");
        printf("%s", e);
        printf("\n\n");
    
        NSString* reason = [NSString stringWithUTF8String:e];
        NSString* name = reason;
        
        NSException *exception = [NSException
                          exceptionWithName:name
                          reason: reason
                          userInfo:nil];
        @throw exception;
    }
    return false;
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
