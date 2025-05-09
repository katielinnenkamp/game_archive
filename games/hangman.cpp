#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

// hangman game: 1 player gives a word, 1 player guesses letters
int main() {
    string word;
    string guessedWord;
    char guess;
    int attempts = 6;

    cout << "=== Hangman Game 🎮 ===\n";
    cout << "Enter a word for the other player to guess: ";
    cin >> word;

    // Initialize guessedWord with underscores
    guessedWord = string(word.length(), '_');

    cout << "\nThe word has " << word.length() << " letters.\n";
    cout << "You have " << attempts << " attempts to guess the word.\n";

    while (attempts > 0 && guessedWord != word) {
        cout << "\nCurrent word: " << guessedWord << "\n";
        cout << "Enter a letter to guess: ";
        cin >> guess;

        bool correctGuess = false;
        for (size_t i = 0; i < word.length(); ++i) {
            if (word[i] == guess) {
                guessedWord[i] = guess;
                correctGuess = true;
            }
        }

        if (!correctGuess) {
            --attempts;
            cout << "Incorrect guess! You have " << attempts << " attempts left.\n";
        }
    }

    if (guessedWord == word) {
        cout << "\nCongratulations! You've guessed the word: " << word << "\n";
    } else {
        cout << "\nGame over! The word was: " << word << "\n";
    }

    return 0;
}
