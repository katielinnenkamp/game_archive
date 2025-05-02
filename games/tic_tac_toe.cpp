#include <iostream>
using namespace std;

char board[3][3] = {{'1','2','3'},
                    {'4','5','6'},
                    {'7','8','9'}};

char current_marker;
int current_player;

void drawBoard() {
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        cout << " ";
        for (int j = 0; j < 3; j++) {
            cout << board[i][j];
            if (j < 2) cout << " | ";
        }
        cout << "\n";
        if (i < 2) cout << "---|---|---\n";
    }
    cout << "\n";
}

bool placeMarker(int slot) {
    int row = (slot - 1) / 3;
    int col = (slot - 1) % 3;

    if (board[row][col] == 'X' || board[row][col] == 'O') {
        return false;
    }

    board[row][col] = current_marker;
    return true;
}

int winner() {
    // Rows, Columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return current_player;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return current_player;
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return current_player;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return current_player;

    return 0;
}

void game() {
    cout << "Tic-Tac-Toe ✨ Player 1 will be X, Player 2 will be O.\n";
    drawBoard();

    for (int turn = 0; turn < 9; turn++) {
        current_player = (turn % 2) + 1;
        current_marker = (current_player == 1) ? 'X' : 'O';

        int slot;
        cout << "Player " << current_player << " (" << current_marker << "), choose your slot (1-9): ";
        cin >> slot;

        if (slot < 1 || slot > 9 || !placeMarker(slot)) {
            cout << "Invalid move. Try again.\n";
            turn--; // repeat turn
            continue;
        }

        drawBoard();
        if (winner() != 0) {
            cout << "🎉 Player " << current_player << " wins!\n";
            return;
        }
    }

    cout << "😐 It's a tie!\n";
}

int main() {
    game();
    return 0;
}