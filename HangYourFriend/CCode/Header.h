//
//  Header.h
//  HangYourFriend
//
//  Created by Harold Hatch on 10/8/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//
#ifdef __cplusplus
extern "C"{
#endif
    
    class Stage
    {
        private:
            int state;
        
        public:
            Stage(int);
            ~Stage();
            int getState();
    };
#ifdef __cplusplus
}
#endif 


