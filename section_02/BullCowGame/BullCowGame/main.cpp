/*  This is the console executable, that makes use of the BullCow class
 This acts as the view in a MVC pattern  and is responsible for all 
 user interaction, for game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGames.hpp"

using FText = std::string;

void PrintIntro();
void PrintGameSummary();
void PlayGame();
bool PlayAgain();
FText GetValidGuess();
FBullCowGame BCGame; //instantiate a new game.

int32 main()
{
    bool bPlayAgain = false;
    
    do {
        PrintIntro();
        PlayGame();
        //TODO add a game summary at the end
        bPlayAgain = PlayAgain();
    } while(bPlayAgain);
    
    return 0;
}

void PrintIntro() {
    //introduce the game
    std::cout << "Welcome to Bulls and Cows, a fun word game" << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWorldLength();
    std::cout << " letter isogram I am thinking of?\n";
}

void PrintGameSummary() {
    if(BCGame.IsGameWon()){
        std::cout << "Congratulations You Won The Game!!!" << std::endl;
    } else {
        std::cout << "Sorry you didn't win, but should try another time" << std::endl;
    }
    std::cout << std::endl;
}

void PlayGame() {
    
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();
    
    std::cout << "Max Number of tries : " << MaxTries << std::endl;
    
    
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
        FText Guess = GetValidGuess();
        
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        //print Nums of bulls and cows
        std::cout << "Bulls: = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

    }
    
    //TODO summarize game
    PrintGameSummary();
}

FText GetValidGuess() {
    
    EGuessStatus status = EGuessStatus::Invalid_Status;
    FText Guess;
    do {
        int32 CurrentTry = BCGame.GetCurrentTry();
        
        
        std::cout << "Try " << CurrentTry << ". Enter your guess: ";
        std::getline(std::cin, Guess);
        
        status = BCGame.CheckGuessValidity(Guess);
        //repeat the guess to the user
        
        switch(status) {
            case EGuessStatus::Not_Isogram :
                std::cout << "Please the word should be an isogram" << std::endl;
                break;
            case EGuessStatus::Wrong_Length:
                std::cout << "Wrong Length, Please enter a "<< BCGame.GetHiddenWorldLength() << " letter word" << std::endl;
                break;
            case EGuessStatus::Not_Lower_Case :
                std::cout << "Word should be lower case" << std::endl;
                break;
            default :
                break;
        }
        std::cout << std::endl;
    } while(status != EGuessStatus::OK);
    
    return Guess;
}



bool PlayAgain() {
    FText PlayerResponse;
    std::cout << "Would you like to play again? (y/n)" << std::endl;
    //std::cin >> PlayerResponse;
    std::getline(std::cin, PlayerResponse);
    
    if(PlayerResponse == "y") {
        return true;
    } else if(PlayerResponse == "n"){
        return false;
    } else {
        std::cout << "Incorrect answer" << std::endl;
        return PlayAgain();
    }
}
