#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// game: Flip a Coin - input should just be a ' ', then output should be "You got heads" or "You got tails"
int main() {
    srand(time(0)); // Seed for random number generation
    int coin = rand() % 2; // Random number between 0 and 1

    cout << "=== Flip a Coin Game 🎲 ===\n";
    cout << "Press Enter to flip the coin...\n";
    cin.get(); // Wait for user input

    if (coin == 0) {
        cout << "You got heads! \n";
    } else {
        cout << "You got tails! \n";
    }

    return 0;

}