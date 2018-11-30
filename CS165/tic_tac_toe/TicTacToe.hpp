/*********************************************************************
** Author: Josh Huff
** Date: December 2, 2016
** Description: Project 10.a -- TicTacToe.hpp -- TicTacToe game class definition
*********************************************************************/

#ifndef TICTACTOE_HPP
#define TICTACTOE_HPP

class TicTacToe
{

    private:
        Board gameBoard;
        char playerTurn;
        
    public:
        TicTacToe(char);
        void play();
};

#endif
