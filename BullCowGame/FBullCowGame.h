#pragma once
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <cstdlib>
#define Tmap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;

};

enum class EGuessStatus
{	//Enum class has scope
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lower_Case

};


class FBullCowGame
{
public:
	FBullCowGame();
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	void ShowHiddenWord() { std::cout << "The HIDDEN_WORD was : " << MyHiddenWord << " \n"; }

	EGuessStatus CheckGuessValidity(FString Guess); //TODO

	FBullCowCount SubmitValidGuess(FString Guess);



private:
	int32 MyCurrentTry ;
	int32 MyMaxTries ;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString Word) const;
	bool IsLowerCase(FString Word) const;

	FString GenerateRandomWord();
	

};

