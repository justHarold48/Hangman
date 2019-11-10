//
//  Stage.h
//  HangYourFriend
//
//  Created by Harold Hatch on 10/8/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#ifndef Stage_h
#define Stage_h

class Stage
{
    private:
        int state;
    
    public:
        Stage(int);
        ~Stage();
        int getState() const;
        void addBodyPart();
};

#endif /* Stage_h */
