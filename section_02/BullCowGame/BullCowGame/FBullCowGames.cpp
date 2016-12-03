//
//  FBullCowGames.cpp
//  BullCowGame
//
//  Created by Massimo Crapanzano on 11/25/16.
//  Copyright © 2016 Massimo Crapanzano. All rights reserved.
//

#include "FBullCowGames.hpp"
#include <map>
#define TMap std::map


FBullCowGame::FBullCowGame(){
    Reset();
}

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "ant";
    
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    bGameWon = false;
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
    return bGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string Guess) const{
    
    //if the guess isn't an isogram
    if(!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    } else if(!IsLowerCase(Guess)) {
        //if the guess isn't all lower case
        //return error
        return EGuessStatus::Not_Lower_Case;
        
    } else if (GetHiddenWorldLength() != Guess.length()){
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
    int32 WordLength = GetHiddenWorldLength();
    for(int32 i = 0; i < WordLength; i++) {
        //compare letters against the hidden word
        for(int32 j = 0; j < WordLength; j++) {
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
    if(BullCowCount.Bulls == WordLength) {
        bGameWon = true;
    } else {
        bGameWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const{
    if(Word.length() <= 1) { return true; }
    TMap<char, bool> LetterSeen;
    
    for(auto Letter: Word) {
        Letter = tolower(Letter);
        if(!LetterSeen[Letter]) {
            LetterSeen[Letter] = true;
        } else {
            return false;
        }
    }
    
    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const {
    for(auto Letter : Word) {
        if(!islower(Letter)){
            return false;
        }
    }
    return true;
}




