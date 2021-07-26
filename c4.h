#include <vector>

const char  EVENCHAR = 'X';
const char ODDCHAR = 'O';
const char EMPTYCHAR = ' ';
const int EVENINT = 0;
const int ODDINT =  1;
const int EMPTYINT = -1;
const long long LSB1 = 1;
typedef long long bitboard;

class Board {
    public:
        bool checkWin();
        int gameOver();
        void makeMove(int column);
        void undoMove();
        std::vector<int> validMoves();
        void output();
        int getCounter();
    private:
        bitboard boards[2] = {0,0}; //[0] for X, [1] for O
        int heights[7] = {0,7,14,21,28,35,42}; //Bit at the bottom of each column
        int counter = 0; //Number of turns, identifies current player
        //(count & 1) => 1 if odd, 0 if even. 
        //also used to index boards.and moves
        int moves[42] = {-1};
};

class Game {
    public:
        Board board;

        void turn();
};