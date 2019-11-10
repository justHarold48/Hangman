//
//  Stage.hpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif
    class Stage
    {
        private:
            int state;
            string stake;
            string base;
            string word;
            string prevGuessList;

        public:
            //
            // Constructor
            //
            Stage(void);

            //
            // Deconstructor
            //
            virtual ~Stage() = default; 

            //
            // adds stake and base according to word entered
            //
            void initStage(const char*); 

            //
            // forces the current stage to change to it's next state
            //
            void nextStageState() noexcept(false); 

            //
            // returns current stage
            //
            string getStage(void); 

            //
            // returns complete stage
            //
            string getCompleteStage(void); 

            //
            // returns true if char in word else returns false
            //
            bool makeGuess(char) noexcept(false); 

            //
            // returns state of stage.
            //
            int getState(void);

      private:
            //
            // adds a letter to the base
            //
            void insertBaseLetter(char);

            //
            // returns the current state of the stake
            //
            string getStakeState(int state);
    };

#ifdef __cplusplus
}
#endif
