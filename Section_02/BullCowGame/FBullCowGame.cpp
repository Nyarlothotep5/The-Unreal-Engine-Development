#include "FBullCowGame.h"
#include <cstdlib>
#include <time.h>
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FString Isograms[] = { "ladybug", "planet", "lab", "triangle", "isogram", "plane", "plant", "cave", "jew", "chair", "hair", "clash", "star", "bump", "cow", "snake", "chart", "cumin"};

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,6}, {5,9}, {6,13}, {7,18}, {8,25} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if( Guess.length() != GetHiddenWordLength() ) { return EGuessStatus::Wrong_Length; }
	if( !IsIsogram(Guess) ) { return EGuessStatus::Not_Isogram; }
	if( ContainsNumber(Guess) ) { return EGuessStatus::Number_Included; }
	if( !IsLowercase(Guess) ) { return EGuessStatus::Not_Lowercase; }

	return EGuessStatus::OK;
}

bool FBullCowGame::ContainsNumber(FString Word) const
{
	for( auto Letter : Word ) {
		if( isdigit(Letter) ) { return true; }
	}

	return false;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for( auto Letter : Word ) {
		if( !islower(Letter) ) { return false; }
	}

	return true;
}

void FBullCowGame::Reset()
{
	srand(time(NULL));
	const FString HIDDEN_WORD = Isograms[rand() % (sizeof(Isograms)/sizeof(*Isograms))];

	int HiddenWordLength = HIDDEN_WORD.length();
	const int32 MAX_TRIES = int32((HiddenWordLength*HiddenWordLength - HiddenWordLength) / 3.0);

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

void FBullCowGame::IncreaseTryNumber()
{
	MyCurrentTry++;
	return;
}

//receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//increment turn number
	IncreaseTryNumber();

	//setup a return variabla
	FBullCowCount BullCowCount;

	int32 GuessLength = Guess.length();
	int32 WordLength = MyHiddenWord.length();	//assuming guess is a valid word

	for( int32 GChar = 0; GChar < GuessLength; GChar++ )
	{
		for( int32 HWChar = 0; HWChar < WordLength; HWChar++ )
		{
			if( Guess[GChar] == MyHiddenWord[HWChar] && GChar != HWChar ) { 
				BullCowCount.Cows++; 
			}
			else if( Guess[GChar] == MyHiddenWord[HWChar] && GChar == HWChar ) { 
				BullCowCount.Bulls++; 
			}
		}
	}

	if( Guess == MyHiddenWord ) { bGameWon = true; }
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 or 1 letter strings as isograms
	if( Word.length() <= 1 ) { return true; }

	TMap<char, bool> LetterSeen;

	for( auto Letter : Word )	//for all letters of the word
	{
		Letter = tolower(Letter);

		if( LetterSeen[Letter] ) { 
			return false; 
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}
