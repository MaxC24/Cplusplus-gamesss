/*  This is the console executable, that makes use of the BullCow class
 This acts as the view in a MVC pattern  and is responsible for all 
 user interaction, for game logic see the FBullCowGame class.
 */

#include <iostream>
#include <string>
#include "FBullCowGames.hpp"

using FText = std::string;

void PrintIntro();
void PlayGame();
bool PlayAgain();
FText GetGuess();
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

void PlayGame() {
    
    BCGame.Reset();
    int32 maxTries = BCGame.GetMaxTries();
    
    std::cout << maxTries << std::endl;
    
    
    constexpr int32 TIMES = 5;
    for(int32 i = 0; i < TIMES; i++) {
        FText Guess = GetGuess(); //TODO make loop checking valid
        EGuessStatus status = BCGame.CheckGuessValidity(Guess);
        //submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
        //print Nums of bulls and cows
        std::cout << "Bulls: = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;

    }
    
    //TODO summarize game
}

FText GetGuess() {
    
    int32 CurrentTry = BCGame.GetCurrentTry();
    FText Guess;
    std::cout << "Try " << CurrentTry << ". Enter your guess: ";
    std::getline(std::cin, Guess);
    //repeat the guess to the user
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
