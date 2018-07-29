/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void ReturnGuessBack(FText Guess);
void PlayGame();
FText GetValidGuess();
void SubmitValidGuess(FText CurrentGuess);
FText GetGuess();
bool AskToPlayAgain();
void PrintResults();

FBullCowGame BCGame;

//the entry point for this app
int main()
{
	bool bPlayAgain = false;
	do {
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while( bPlayAgain );

	return 0;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	PrintIntro();

	//loop for getting guesses, with an additional limit
	while(BCGame.GetCurrentTry() <= MaxTries && !BCGame.IsGameWon())
	{
		FText Guess = GetValidGuess();
		ReturnGuessBack(Guess);
		SubmitValidGuess(Guess);
	}

	PrintResults();
}

FText GetValidGuess()
{
	EGuessStatus LoopStatus = EGuessStatus::Invalid;
	FText MyGuess = "";

	do
	{
		MyGuess = GetGuess();
		EGuessStatus Status = BCGame.CheckGuessValidity(MyGuess);

		switch( Status )
		{
		case EGuessStatus::OK:
			LoopStatus = EGuessStatus::OK;
			return MyGuess;
			break;

		case EGuessStatus::Wrong_Length:
			std::cout << "Your guess has wrong length! Try again.\n" << std::endl;
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess is not an isogram! Try again.\n" << std::endl;
			break;

		case EGuessStatus::Number_Included:
			std::cout << "Your guess contains a number! Try again.\n" << std::endl;
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Your guess contains uppercase letters! Try again.\n" << std::endl;
			break;
		}
	} while( LoopStatus != EGuessStatus::OK );

	return MyGuess;
}

void SubmitValidGuess(FText CurrentGuess)
{
	FBullCowCount BullsCows;
	BullsCows = BCGame.SubmitValidGuess(CurrentGuess);

	std::cout << "Number of bulls: " << BullsCows.Bulls << std::endl;
	std::cout << "Number of cows: " << BullsCows.Cows << std::endl << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "\nDo you want to play again? (y/n)" << std::endl;
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}

void PrintIntro()
{
	//introduce the game
	std::cout << "Welcome to Bulls and Cows, the word game!" << std::endl <<std::endl;
	std::cout << "	       {{ __ }}		  ~~__~~" << std::endl;
	std::cout << "		| ^^ |		  | -- |" << std::endl;
	std::cout << "		 \\../		   \\../ " << std::endl;
	std::cout << "							" << std::endl;
	std::cout << "		 BULL		    COW"<< std::endl;
	std::cout << ""<< std::endl;

	const int32 WORD_LENGTH = BCGame.GetHiddenWordLength();
	std::cout << "Can you guess the " << WORD_LENGTH << "-letter isogram I'm thinking of?" << std::endl << std::endl;
	return;
}

FText GetGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	//get a guess from the player
	std::cout << "Try " << CurrentTry << "/" << BCGame.GetMaxTries() << ". Please type in your guess: ";

	FText Guess = "";
	std::getline(std::cin, Guess);

	return Guess;
}

void ReturnGuessBack(FText Guess)
{
	//repeat the guess back to the player
	std::cout << "Your guess is: " << Guess << std::endl;
}

void PrintResults()
{
	if( BCGame.IsGameWon() )
	{
		std::cout << "\nCongrats! That isogram is correct! You won!!!" << std::endl;
		std::cout << "You managed to guess on your " << BCGame.GetCurrentTry() - 1 << " try!" << std::endl;
	}
	else
	{
		std::cout << "Tough luck, maybe you'll guess the isogram next time!" << std::endl;
	}
}