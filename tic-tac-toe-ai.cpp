#include <iostream>
#include <vector>
using namespace std;

vector<char> board ={'1','2','3','4','5','6','7','8','9'}; 
void printboard(){
    cout << '\n';
    for(int i =0;i<board.size();i++){
        cout<<board[i]<<" ";
        if ((i + 1) % 3 == 0)
            cout << "\n-----------\n";
        else
            cout << " | ";
    }
}

bool makemove(char palyer,int pos){
    if (pos<1 || pos > 9 || board[pos-1] == 'X' || board[pos-1] == 'O')
    {
        cout << "Invalid Move";
        return false;
    }
    board[pos-1]=palyer;
    return true;
    
}

bool checkWin(char player) {
    // Horizontal
    if ((board[0] == player && board[1] == player && board[2] == player) ||
        (board[3] == player && board[4] == player && board[5] == player) ||
        (board[6] == player && board[7] == player && board[8] == player))
        return true;

    // Vertical
    if ((board[0] == player && board[3] == player && board[6] == player) ||
        (board[1] == player && board[4] == player && board[7] == player) ||
        (board[2] == player && board[5] == player && board[8] == player))
        return true;

    // Diagonals
    if ((board[0] == player && board[4] == player && board[8] == player) ||
        (board[2] == player && board[4] == player && board[6] == player))
        return true;

    return false;
}

bool isMovesLeft() {
    for (char c : board) {
        if (c != 'X' && c != 'O')
            return true;
    }
    return false;
}

int evaluate() {
    if (checkWin('O')) return +10;
    if (checkWin('X')) return -10;
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
                board[i] = 'O';
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
                board[i] = 'X';
                best = min(best, minimax(true));
                board[i] = backup;
            }
        }
        return best;
    }
}


int findBestMove() {
    int bestVal = -1000;
    int bestMove = -1;

    for (int i = 0; i < 9; i++) {
        if (board[i] != 'X' && board[i] != 'O') {
            char backup = board[i];
            board[i] = 'O';
            int moveVal = minimax(false);
            board[i] = backup;

            if (moveVal > bestVal) {
                bestVal = moveVal;
                bestMove = i;
            }
        }
    }

    return bestMove + 1; // since makemove expects 1-9
}

int main(){
    int movescount = 0;
    char player1 = 'X';//human
    char player2 = 'O';//ai
    char currplayer = player2;

    while (movescount<9)
    {
        printboard();
        int pos;
        if (currplayer == player2)
        {
            pos = findBestMove();
            cout << "AI Chooses " << pos;
        }else{
            cout << currplayer << " enter position (1-9): ";
            cin >> pos;
        }
        if (makemove(currplayer, pos)) {
            movescount++;

            if (checkWin(currplayer)) {
                printboard();
                if (currplayer == player2)
                    cout << "AI wins! " << endl;
                else
                    cout << "Player " << currplayer << " wins! 🎉" << endl;
                return 0;
            }

            if (!isMovesLeft()) {
                printboard();
                cout << "It's a draw!" << endl;
                return 0;
            }

            // Switch players
            currplayer = (currplayer == player1) ? player2 : player1;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
    printboard();
    cout << "Game over.\n";
    return 0;
}