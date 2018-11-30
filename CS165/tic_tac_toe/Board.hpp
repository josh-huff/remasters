/*********************************************************************
** Author: Josh Huff
** Date: December 2, 2016
** Description: Project 10.a -- Board.hpp -- TicTacToe Board class definition
*********************************************************************/

#ifndef BOARD_HPP
#define BOARD_HPP

enum State {IN_PROGRESS, X_WINS, O_WINS, DRAW};

class Board
{

    private:
        char boardPosition[3][3];

        // Helper methods (for 11/2018 "remaster")
        int _checkForWin();
        int _diagWin();
        int _horiWin();
        int _vertWin();
        bool _isBoardFull();
        
    public:
        Board();
        bool makeMove(int, int, char);
        State gameState();
        void print();
};

#endif
