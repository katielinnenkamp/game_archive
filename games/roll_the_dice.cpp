#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// game: Roll the Dice - input should just be a ' ', then output should be "You rolled a 1" to "You rolled a 6"
int main() {
    srand(time(0)); // Seed for random number generation
    int dice = rand() % 6 + 1; // Random number between 1 and 6

    cout << "=== Roll the Dice Game 🎲 ===\n";
    cout << "Press Enter to roll the dice...\n";
    cin.get(); // Wait for user input

    cout << "You rolled a " << dice << "!\n";

    return 0;
}