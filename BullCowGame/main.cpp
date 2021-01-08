#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <iomanip>
#include <map>

#define TMap std::map

using namespace std;

using FText = std::string;
using int32 = int;



void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame;

int main()
{	
	do
	{
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		

	} while (AskToPlayAgain());
	
	


	return 0;
}

void PlayGame()
{	
	//BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	int32 CurrentTry = BCGame.GetCurrentTry();

	//loop for the number of turns asking for guesses
	//TODO chane from FOR toWhile loop onece we are validating tries
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry()<=MaxTries)
	{
		FText guess = GetValidGuess();
		

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);
		//Print number of bulls and cows

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << endl;
		//Repeat the guess back
		//cout << "Your guess was: " << guess << endl;

		cout << endl;
	}

	PrintGameSummary();

}

void PrintIntro()
{																			  

	std::cout << "Welcome to Bulls and Cows" << std::endl;							   
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of ?\n" << endl;
}

FText GetValidGuess()
{	
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	
	do
	{
		//Get a guess from the player
		cout << "TRY [" << BCGame.GetCurrentTry() << "]"<<"of[" << BCGame.GetMaxTries()<<"] " << "Enter your guess: ";
		
		//FBullCowGame BCGame;
		FText guess = "";
		getline(cin, guess);
		Status = BCGame.CheckGuessValidity(guess);
		//TODO input validation
		
		switch (Status)
		{
		case EGuessStatus::Not_Isogram: cout << "Please enter a Isogram word (all letters are unique).\n";
			break;
		case EGuessStatus::Wrong_Length: cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Lower_Case: cout << "Please enter all lowercase letters.\n";
			break;
		default: return guess;
		}
		cout << endl;

	} while (Status != EGuessStatus::OK);

	
	
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again? (y/n)";
	FText Response = "";
	getline(cin, Response);

	if (Response[0] == 'y' || Response[0] == 'Y')
	{	
		cout << endl;
		return true;
	}
	 
	return false;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		cout << "WELL DONE - YOU WIN!\n";

	}
	else
	{
		cout << "GAME OVER - YOU LOST!\n";
		BCGame.ShowHiddenWord();
	}

}
