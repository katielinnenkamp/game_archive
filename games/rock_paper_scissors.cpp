#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
    string options[3] = {"Rock ✊", "Paper 📄", "Scissors ✂️"};
    int userChoice, computerChoice;

    cout << "=== Rock, Paper, Scissors Game 🎮 ===\n";
    cout << "Choose one:\n";
    cout << "0 - Rock ✊\n";
    cout << "1 - Paper 📄\n";
    cout << "2 - Scissors ✂️\n";
    cout << "Enter your choice: ";
    cin >> userChoice;

    if (userChoice < 0 || userChoice > 2) {
        cout << "❌ Invalid choice. Please enter 0, 1, or 2.\n";
        return 1;
    }

    srand(time(0));
    computerChoice = rand() % 3;

    cout << "You chose: " << options[userChoice] << endl;
    cout << "Computer chose: " << options[computerChoice] << endl;

    if (userChoice == computerChoice) {
        cout << "It's a tie! stop copying me 😒 \n";
    } else if ((userChoice == 0 && computerChoice == 2) ||
               (userChoice == 1 && computerChoice == 0) ||
               (userChoice == 2 && computerChoice == 1)) {
        cout << "🎉 You win! Congrats… Did you cheat? be honest! 😏\n";
    } else {
        cout << "💀 You lose. That was embarrassing. I hope no one saw that.\n";
    }

    return 0;
}