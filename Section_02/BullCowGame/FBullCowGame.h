#pragma once
#include<string>

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase,
	Number_Included,
	Invalid
};

enum class EResetStatus
{
	OK,

};

class FBullCowGame
{
public:
	FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;

	void Reset();
	void IncreaseTryNumber();
	
	FBullCowCount SubmitValidGuess(FString);

private:
	//see constructor for initialisation
	bool IsIsogram(FString) const;
	bool ContainsNumber(FString) const;
	bool IsLowercase(FString) const;

	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameWon;
};