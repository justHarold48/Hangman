//
//  StageWrapper.h
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface StageWrapper : NSObject

- (void)initStage:(const char*)length;

- (void)addBodyPart;

- (int)getState;

- (NSString*)getStage;

- (NSString*)getCompleteStage;

- (bool)makeGuess:(const char)letter ;

- (BOOL)catchException:(void(^)())tryBlock error:(__autoreleasing NSError **)error;

@end
