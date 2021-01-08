#include "FBullCowGame.h"


FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{	
	//const FString HIDDEN_WORD = "planet";
	FString HIDDEN_WORD = GenerateRandomWord();
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bIsGameWon = false;
}

int32 FBullCowGame::GetMaxTries ()const
{	
	Tmap<int32, int32> WordLengthToMaxTries{ {3,7} , {4,10} , {5,13} , {6, 16} , {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()];
	
}

int32 FBullCowGame::GetCurrentTry()const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.size();
}

bool FBullCowGame::IsGameWon() const
{
	return bIsGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess)
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lower_Case;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

//Recieve a VALID guess , increment turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{	
	//increment turn..setup return variable...loop to all letters...compare letters againts hidden word
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 HiddenWordLenght = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLenght; i++)
	{
		for (int32 j = 0; j < HiddenWordLenght; j++)
		{
			if (Guess[i] == MyHiddenWord[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLenght)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}



	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{	
	if (Word.length() <= 1) { return true; }
	Tmap<char, bool> LetterSeen;
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}


	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
	}


	return true;
}

FString FBullCowGame::GenerateRandomWord()
{
	std::vector<FString> words =
	{
		"zip","zap","hex","fox","joy","jaw","wax","mix","jar","sex",
		"taye","anus","soup","cork","reef","baba","same","sand","unit","robe",
		"cakes","camel","lance","later","parts","palet","yacht","satin","score","olive",
		"debris","decoys","handle","abused","actors","advice","ingots","inform","vector","length"
	};

	srand((unsigned)time(0));
	int NumberIndex;
	NumberIndex = rand() % (words.size());

	return words[NumberIndex];


}
