#include <iostream>
#include <vector>
using namespace std;

vector<char> board = {'1','2','3','4','5','6','7','8','9'};

void printboard(){
    cout << '\n';
    for(int i = 0; i < board.size(); i++) {
        cout << board[i] << " ";
        if ((i + 1) % 3 == 0)
            cout << "\n-----------\n";
        else
            cout << " | ";
    }
}

bool makemove(char player, int pos){
    if (pos < 1 || pos > 9 || board[pos - 1] == 'X' || board[pos - 1] == 'O') {
        cout << "Invalid Move\n";
        return false;
    }
    board[pos - 1] = player;
    return true;
}

bool checkWin(char player) {
    return
    // Horizontal
    (board[0] == player && board[1] == player && board[2] == player) ||
    (board[3] == player && board[4] == player && board[5] == player) ||
    (board[6] == player && board[7] == player && board[8] == player) ||

    // Vertical
    (board[0] == player && board[3] == player && board[6] == player) ||
    (board[1] == player && board[4] == player && board[7] == player) ||
    (board[2] == player && board[5] == player && board[8] == player) ||

    // Diagonals
    (board[0] == player && board[4] == player && board[8] == player) ||
    (board[2] == player && board[4] == player && board[6] == player);
}

bool isMovesLeft() {
    for (char c : board) {
        if (c != 'X' && c != 'O')
            return true;
    }
    return false;
}

int evaluate() {
    if (checkWin('X')) return +10;
    if (checkWin('O')) return -10;
    return 0;
}

int minimax(bool isMax) {
    int score = evaluate();
    if (score == 10 || score == -10)
        return score;
    if (!isMovesLeft())
        return 0;

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char backup = board[i];
                board[i] = 'X';
                best = max(best, minimax(false));
                board[i] = backup;
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 9; i++) {
            if (board[i] != 'X' && board[i] != 'O') {
                char backup = board[i];
                board[i] = 'O';
                best = min(best, minimax(true));
                board[i] = backup;
            }
        }
        return best;
    }
}

int findBestMove(char player) {
    int bestVal = (player == 'X') ? -1000 : 1000;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char backup = board[i];
            board[i] = player;
            int moveVal = minimax(player == 'O'); // O is minimizing
            board[i] = backup;

            if ((player == 'X' && moveVal > bestVal) || (player == 'O' && moveVal < bestVal)) {
                bestVal = moveVal;
                bestMove = i;
            }
        }
    }

    return bestMove + 1;
}

int main(){
    char ai1 = 'X'; // AI1
    char ai2 = 'O'; // AI2
    char currplayer = ai1;
    int moveCount = 0;

    while (isMovesLeft()) {
        printboard();
        int pos = findBestMove(currplayer);
        cout << "AI " << currplayer << " chooses " << pos << endl;
        makemove(currplayer, pos);
        moveCount++;

        if (checkWin(currplayer)) {
            printboard();
            cout << "AI " << currplayer << " wins the game! " << endl;
            return 0;
        }

        currplayer = (currplayer == ai1) ? ai2 : ai1;
    }

    printboard();
    cout << "It's a draw! " << endl;
    return 0;
}
