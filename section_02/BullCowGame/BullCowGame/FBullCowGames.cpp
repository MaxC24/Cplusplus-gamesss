//
//  FBullCowGames.cpp
//  BullCowGame
//
//  Created by Massimo Crapanzano on 11/25/16.
//  Copyright © 2016 Massimo Crapanzano. All rights reserved.
//

#include "FBullCowGames.hpp"
#include <string>


FBullCowGame::FBullCowGame(){
    Reset();
}

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "ant";
    
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    return;
}

int32 FBullCowGame::GetMaxTries() const {
    return MyMaxTries;
}

int32 FBullCowGame::GetCurrentTry() const{
    return MyCurrentTry;
}

bool FBullCowGame::IsGameWon() const{
    return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string) const{
    
    //if the guess isn't an isogram
    if(false) {
        return EGuessStatus::Not_Isogram;
    } else if(false) {
        //if the guess isn't all lower case
        //return error
        return EGuessStatus::Not_Lower_Case;
        
    } else if (false){
        //If the Guess length is wrong
        //return error
        return EGuessStatus::Wrong_Length;
    } else {
        //Otherwise
        //return ok
        return EGuessStatus::OK;
    }
}

int32 FBullCowGame::GetHiddenWorldLength() const{
    return MyHiddenWord.length();
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    //increment the turn number
    MyCurrentTry++;
    //setup a return value
    FBullCowCount BullCowCount;
    int32 HiddenWordLength = GetHiddenWorldLength();
    for(int32 i = 0; i < HiddenWordLength; i++) {
        //compare letters against the hidden word
        for(int32 j = 0; j < HiddenWordLength; j++) {
        // if they match  then
            if(MyHiddenWord[i] == Guess[j]){
                //if they are in the same place
                if(i == j) {
                    //increment bulls
                    BullCowCount.Bulls++ ;
                } else {
                    //else increment cows
                    BullCowCount.Cows++ ;

                }
                
            }

        }
    }
    return BullCowCount;
}
