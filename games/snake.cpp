#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <cstdlib>
#include <sys/ioctl.h>

using namespace std;

const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100], nTail;

enum Direction { LEFT, RIGHT, UP, DOWN };
Direction dir = RIGHT;
bool gameOver = false;

void disableBuffering() {
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
}

int kbhit() {
    int bytesWaiting;
    ioctl(STDIN_FILENO, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

char getInput() {
    char ch;
    read(STDIN_FILENO, &ch, 1);
    return ch;
}

void Setup() {
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    dir = RIGHT;
    disableBuffering();
}

void Draw() {
    system("clear");
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) cout << "#";
            if (i == y && j == x) cout << "O";
            else if (i == fruitY && j == fruitX) cout << "O";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                        break;
                    }
                }
                if (!print) cout << " ";
            }
            if (j == width - 1) cout << "#";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++) cout << "#";
    cout << "\nScore: " << score << endl;
}

void Input() {
    if (!kbhit()) return;
    char ch = getInput();

    if (ch == '\033') { // arrow keys
        if (getInput() == '[') {
            char arrow = getInput();
            switch (arrow) {
                case 'A': if (dir != DOWN) dir = UP; break;
                case 'B': if (dir != UP) dir = DOWN; break;
                case 'C': if (dir != LEFT) dir = RIGHT; break;
                case 'D': if (dir != RIGHT) dir = LEFT; break;
            }
        }
    } else {
        switch (ch) {
            case 'w': if (dir != DOWN) dir = UP; break;
            case 's': if (dir != UP) dir = DOWN; break;
            case 'a': if (dir != RIGHT) dir = LEFT; break;
            case 'd': if (dir != LEFT) dir = RIGHT; break;
            case 'x': gameOver = true; break;
        }
    }
}

void Logic() {
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir) {
        case LEFT: x--; break;
        case RIGHT: x++; break;
        case UP: y--; break;
        case DOWN: y++; break;
    }

    if (x < 0 || x >= width || y < 0 || y >= height)
        gameOver = true;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;

    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
    }
}

int main() {
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        usleep(120000); // 0.12 sec
    }

    cout << "\nGame Over! Final Score: " << score << endl;
    return 0;
}