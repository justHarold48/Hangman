//
//  Stage.hpp
//  Hang Your Friend
//
//  Created by Harold Hatch on 10/9/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

#include <string>
#include <unordered_set>

#ifdef __cplusplus
extern "C"
{
#endif
    
class Stage {
public:
    //
    // Constructor
    //
    Stage(void) = default;

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
    const std::string getStage(void) const {return (stake_ + base_);}
    
    //
    // returns remaining unguessed letters
    //
    const std::string& getRemainingLetters() const {return remaining_;}

    //
    // returns state of stage.
    //
    unsigned getState(void) const {return state;}

    //
    // returns complete stage
    //
    std::string getCompleteStage(void);

    //
    // returns true if char in word else returns false
    //
    bool makeGuess(char) noexcept(false);

    //
    // adds body part to stake
    //
    void addBodyPart() noexcept(false);

private:
    //
    // adds a letter to the base
    //
    void addLetter(char);
        
private:
    uint8_t state {0};
    std::string stake_;
    std::string base_;
    std::string word_;
    std::string remaining_;
    std::unordered_set<char> prevGuessedLetters_;
};

#ifdef __cplusplus
}
#endif
