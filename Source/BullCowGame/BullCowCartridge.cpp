// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();

    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The HiddenWord is: %s"), *HiddenWord);

    for (int32 Index = 0; Index <= 10; Index++) 
    {
        if (Words[Index].Len() >=  4 && (Words[Index].Len() <=  8)) 
        {
            PrintLine(TEXT("%s"), *Words[Index]);
        } 
    }

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    // If game is over then do ClearScren() and SetupGame() the game
    // else Checking PlayerGuess
    if (bGameOver) {
        ClearScreen();
        SetupGame();
    }
    else {
        ProcessGuess(Input);
    }

}

void UBullCowCartridge::EndGame() {
    bGameOver = true;
    PrintLine(TEXT("Press enter to play again!"));
}

void UBullCowCartridge::SetupGame() {

    // Welcome the player
    PrintLine(TEXT("Welcome to the Bull Cow game!"));

    HiddenWord = TEXT("cakes");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess and ENTER!"));
    PrintLine(TEXT("You have %i lives remaining..."), Lives);

}

void UBullCowCartridge::ProcessGuess(FString Guess) {

    if (Guess == HiddenWord) { // Ends the game if word is correct.
        PrintLine("You Won!");
        EndGame();
        return;
    } 

    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("Sorry, try guessing again.\n You have %i lives remaining"), Lives);
        PrintLine(TEXT("The HiddenWord is %i letters long"), HiddenWord.Len());
        return;
    }

    // check isogram
    if (!IsIsogram(Guess)) {

        PrintLine(TEXT("No repeating letters, guess again"));
        return;
    }

    // remove life
    PrintLine(TEXT("You lost a life!"));
    --Lives;

    if (Lives <= 0) { 
        ClearScreen();
        PrintLine(TEXT("You have no lives left!"));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();
        return;
    }
    PrintLine(TEXT("Guess again, you have %i lives left"), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const {

    for (int32 Index = 0; Index < Word.Len(); Index++) 
    {
        for (int32 Comparison = Index + 1; Comparison < Word.Len(); Comparison++) 
        {
            if (Word[Index] == Word[Comparison]) 
            {
                return false;
            }
        }
    }
    return true;
}