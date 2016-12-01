#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus {
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lower_Case
};

class FBullCowGame {
public:
    FBullCowGame(); //constructor;
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWorldLength() const;
    
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;
    
    
    void Reset(); //TODO make a more rich return value.
    FBullCowCount SubmitGuess(FString);
    
    
    //please try and ignore this and focus on the interface above ^^
private:
    int32 MyCurrentTry;
    int32 MyMaxTries;
    FString MyHiddenWord;
};
