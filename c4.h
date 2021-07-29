#include <vector>
#include <limits>

const char  EVENCHAR = 'X';
const char ODDCHAR = 'O';
const char EMPTYCHAR = ' ';
const int EVENINT = 1;
const int ODDINT =  -1;
const int EMPTYINT = 0;
const int POSINF = std::numeric_limits<int>::max();
const int NEGINF = std::numeric_limits<int>::min();
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
        int evaluate();
    private:
        bitboard boards[2] = {0,0}; //[0] for X, [1] for O
        int heights[7] = {0,7,14,21,28,35,42}; //Bit at the bottom of each column
        int counter = 0; //Number of turns, identifies current player
        //(count & 1) => 1 if odd, 0 if even. 
        //also used to index boards.and moves
        int moves[42] = {-1};
        int evalBoard[64] = {3,4,5,5,4,3,0,
                            4,6,8,8,6,4,0,
                            5,8,11,11,8,5,0,
                            7,10,13,13,10,7,0,
                            5,8,11,11,8,5,0,
                            4,6,8,8,6,4,0,
                            3,4,5,5,4,3,0,
                            0,0,0,0,0,0,0,
                            0,0,0,0,0,0,0,0};
};

class Game {
    public:
        Board board;

        void turn();
        int bestMove();
        int minimax(int depth, int alpha, int beta, bool isMax);
    
    private:
        int maxRecDepth = 10;
};