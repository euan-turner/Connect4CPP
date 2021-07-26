#include <iostream>
#include <algorithm>
#include "v2.h"

using namespace std;

void Board :: makeMove(int column) {
    moves[counter] = column; //Add move to history of moves
    int boardIndex = counter&1; //Index of player bitboard in boards
    long long move = LSB1 << heights[column]; //Bitshift 1 to represent move position
    boards[boardIndex] ^= move; //XOR board with move to play move
    heights[column]++; //Increment base of column
    counter++; //Increment number of moves
}

void Board :: undoMove() {
    counter --; //Decrement count to last move
    int column = moves[counter]; //Get column of last move from move history
    heights[column] --; //Decrement base of column to last move
    long long move = LSB1 << heights[column]; //Bitshift 1 to represent last move position
    int boardIndex = counter&1;
    boards[boardIndex] ^= move; //XOR board to undo move (1 XOR 1 = 0)
    moves[counter] = -1; //Erase move from move history
}

bool Board :: checkWin() {
    int lastCount = counter - 1;
    bitboard b = boards[lastCount&1];
    bitboard bb;
    int directions[4] = {1,7,6,8}; //Vertical, Horizontal, Backward, Forward
    for (int i = 0; i < 4; i ++) {
        int dir = directions[i];
        bb = b & (b >> dir);
        if ((bb & (bb >> (2*dir))) != 0) {
            return true;
        }
    }
    return false;
}

int Board :: gameOver() {
    if (checkWin() == true) {
        return 1;
    } else if (counter == 42) {
        return 0;
    } else {
        return -1;
    }
}

vector<int> Board :: validMoves() {
    vector<int> valid;
    long long topRow = 0b1000000100000010000001000000100000010000001000000; //Ones in 'row' above board
    for (int col = 0; col < 7; col ++) {
        if ((topRow & (LSB1 << heights[col])) == 0) {
            //Simulate a move by shifting to position.
            //If position is not in the top row, move is valid
            valid.push_back(col);
        }
    }
    return valid;
}

void Board :: output() {
    int boardArr[64];
    fill_n(boardArr, 64, EMPTYINT);
    for (int i = 0; i < 64; i ++) {
        if ((boards[0] & (LSB1 << i)) != 0) {
            //Move played by X - even
            boardArr[i] = EVENINT;
        } else if ((boards[1] & (LSB1 << i)) != 0) {
            //Move played by O - odd
            boardArr[i] = ODDINT;
        }
    }
    cout << "\n-----------------------------\n";
    //Print down rows
    for (int row = 5; row > -1; row --) {
        cout << "|";
        //Print across columns
        for (int col = 0; col < 7; col ++) {
            switch(boardArr[row + (col*7)]) {
                case EMPTYINT:
                    cout << ' ' << EMPTYCHAR << ' ' << '|';
                    break;
                case EVENINT:
                    cout << ' ' << EVENCHAR << ' ' << '|';
                    break;
                case ODDINT:
                    cout << ' ' << ODDCHAR << ' ' << '|';
                    break;
            }
        }
        cout <<"\n-----------------------------\n";
    }
    cout << "|";
    for (int i = 1; i < 8; i ++) {
        cout << " " << i << " " << "|";
    }
    cout <<"\n-----------------------------\n";
}

int Board :: getCounter() {
    return counter;
}





void Game :: turn() {
    board.output();
    int col;
    vector<int> valid = board.validMoves();
    if ((board.getCounter()&1) == EVENINT) {
        //Even player turn
        bool validMove = false;
        while (validMove == false) {
            cout << "Enter column (1-7)\n:";
            cin >> col;
            if ((col > 7)||(col < 1)) {
                cout <<"Invalid choice\n";
                continue;
            }
            col --;
            if (*find(valid.begin(), valid.end(), col) == col) {
                validMove = true;
            } else {
                cout << "Column full\n";
            }
        }
    } else {
        //Odd player turn
        bool validMove = false;
        while (validMove == false) {
            cout << "Enter column (1-7)\n:";
            cin >> col;
            if ((col > 7)||(col < 1)) {
                cout <<"Invalid choice\n";
                continue;
            }
            col --;
            if (*find(valid.begin(), valid.end(), col) == col) {
                validMove = true;
            } else {
                cout << "Column full\n";
            }
        }
    }

    board.makeMove(col);

    int status = board.gameOver();
    if (status == 1) {
        cout << "Game won\n";
        board.output();
        exit(0);
    } else if (status == 0) {
        cout << "Game drawn\n";
        board.output();
        exit(0);
    }
}


int main() {
    Game game;
    while (true) {
        game.turn();
    }
}