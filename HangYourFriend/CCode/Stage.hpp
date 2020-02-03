//
//  Stage.hpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
    class Stage
    {
        private:
            int state;
            std::string stake;
            std::string base;
            std::string word;
            std::string prevGuessList;

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
            // returns current stage
            //
            std::string getStage(void);

            //
            // returns complete stage
            //
            std::string getCompleteStage(void);

            //
            // returns true if char in word else returns false
            //
            bool makeGuess(char) noexcept(false);

            //
            // returns state of stage.
            //
            int getState(void);

            //
            // adds body part to stake
            //
            void addBodyPart() noexcept(false);

      private:
            //
            // adds a letter to the base
            //
            void insertLetter(char);

            //
            // returns the current state of the stake
            //
            std::string getStakeState(int state);

    };

#ifdef __cplusplus
}
#endif
