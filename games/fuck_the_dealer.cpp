#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <random>
using namespace std;

// Create and shuffle the deck
vector<string> create_deck() {
    vector<string> order = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    vector<string> deck;
    for (int i = 0; i < 4; ++i) {
        for (const auto& card : order) {
            deck.push_back(card);
        }
    }
    random_device rd;
    mt19937 g(rd());
    shuffle(deck.begin(), deck.end(), g);
    return deck;
}

// Convert card face to numeric value
int card_value(const string& card) {
    if (card == "A") return 1;
    if (card == "J") return 11;
    if (card == "Q") return 12;
    if (card == "K") return 13;
    try {
        return stoi(card);
    } catch (...) {
        return -1;
    }
}

// Get number of players
int get_num_players() {
    int num;
    cout << "Enter the number of players (2-20): ";
    cin >> num;
    while (num < 2 || num > 20) {
        cout << "Invalid input. Please enter a number between 2 and 20: ";
        cin >> num;
    }
    return num;
}

// Get player guess or check for exit
string get_input_guess(const string& player, bool& exit_flag) {
    string guess;
    cout << player << ", guess the card (or type 'exit' or press space): ";
    getline(cin >> ws, guess); // eat whitespace then get full input

    if (guess == " " || guess == "exit" || guess == "EXIT") {
        cout << "Are you sure you want to exit (memory will be lost)? (Type 'y', 'yes', or press space): ";
        string confirm;
        getline(cin >> ws, confirm);
        if (confirm == " " || confirm == "yes" || confirm == "y") {
            exit_flag = true;
        }
        return "";
    }

    return guess;
}

int main() {
    srand(time(0));
    int numPlayers = get_num_players();
    vector<string> playerNames(numPlayers);
    for (int i = 0; i < numPlayers; ++i) {
        cout << "Enter name for player " << (i + 1) << ": ";
        cin >> playerNames[i];
    }

    cin.ignore(); // Clear newline left by cin

    vector<string> deck = create_deck();
    int dealerIndex = 0;
    int dealerPointsInARow = 0;
    int currentPlayer = (dealerIndex + 1) % numPlayers;
    bool exit_flag = false;

    cout << "\nReady to play! Let's begin.\n";

    while (!deck.empty() && !exit_flag) {
        string topCard = deck.back();
        int topValue = card_value(topCard);

        string dealer = playerNames[dealerIndex];
        string guesser = playerNames[currentPlayer];

        cout << "\n" << guesser << "'s turn. Dealer is " << dealer << ". ";
        cout << "Dealer's current points in a row: " << dealerPointsInARow << "\n";

        string first = get_input_guess(guesser, exit_flag);
        if (exit_flag) break;
        int firstGuess = card_value(first);

        bool dealerEarnedPoint = false;

        if (firstGuess == topValue) {
            cout << "Correct! " << dealer << " takes 3 drinks!\n";
            dealerPointsInARow = 0;
        } else {
            cout << "Incorrect. Hint: guess ";
            if (firstGuess < topValue) cout << "higher.\n";
            else cout << "lower.\n";

            string second = get_input_guess(guesser, exit_flag);
            if (exit_flag) break;
            int secondGuess = card_value(second);

            if (secondGuess == topValue) {
                cout << "Correct on second try! " << dealer << " takes 1 drink.\n";
                dealerPointsInARow = 0;
            } else {
                int penalty = abs(secondGuess - topValue);
                cout << "Wrong again! " << guesser << " takes " << penalty << " drinks.\n";
                dealerEarnedPoint = true;
                dealerPointsInARow++;
            }
        }

        // Dealer rotation logic
        if (dealerEarnedPoint && dealerPointsInARow >= 3) {
            cout << dealer << " earned 3 points in a row. Dealer passes the deck to the next player.\n";
            dealerIndex = (dealerIndex + 1) % numPlayers;
            dealerPointsInARow = 0;
            currentPlayer = (dealerIndex + 1) % numPlayers;
        } else {
            // Move to next player, skipping dealer
            currentPlayer = (currentPlayer + 1) % numPlayers;
            if (currentPlayer == dealerIndex) {
                currentPlayer = (currentPlayer + 1) % numPlayers;
            }
        }

        deck.pop_back();
    }

    if (exit_flag) {
        cout << "\nGame exited. Memory cleared.\n";
    } else {
        cout << "\nDeck is empty! Game over.\n";
        cout << "The final dealer was " << playerNames[dealerIndex] << " — they lose!\n";
    }

    return 0;
}
