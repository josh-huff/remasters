#include <iostream>
#include "Board.hpp"

// Constructor: initializes board with all blank spaces
Board::Board(){

    for (int i = 0; i < 3; i++){
        for (int k = 0; k < 3; k++){       
            boardPosition[i][k] = '.';      
        }
    }
}

// Returns false if move is illegal, otherwise completes move and returns true
bool Board::makeMove(int xPos, int yPos, char playerTurn){

    if (boardPosition[xPos][yPos] != '.'){
        return false; 
    }
    
    boardPosition[xPos][yPos] = playerTurn;
    return true;  
}

// Checks for win or draw, returns current board state enum value
State Board::gameState(){

    int game_end = _checkForWin();
    switch(game_end){
        case 0:
            return (_isBoardFull()) ? DRAW : IN_PROGRESS;
        case 1:
            return X_WINS;
        case 2:            
            return O_WINS;
    }      
}

// Prints current board state
void Board::print(){

    std::cout << "   0   1   2\n +-----------+\n";
    for (int i = 0; i < 3; i++){
        std::cout << i << "| ";        
        for (int k = 0; k < 3; k++){       
            std::cout << boardPosition[i][k] << " | ";     
        }
        std::cout << "\n +-----------+\n";
    }   
}

// Checks for all win conditions, returns corresponding state enum value 
int Board::_checkForWin(){

    int dwin = _diagWin();
    int hwin = _horiWin();
    int vwin = _vertWin();

    return dwin + hwin + vwin;
}

// Checks for diagonal win, returns corresponding state enum value
int Board::_diagWin(){

    int status = IN_PROGRESS;
    char center = boardPosition[1][1];
    char topleft = boardPosition[0][0];
    char botleft = boardPosition[2][0];
    char botright = boardPosition[2][2];
    char topright = boardPosition[0][2];

    if(center == '.'){
        // No OP -- skip to returning the default status  
    }else if( (center == topleft) && (center == botright) ||
              (center == botleft) && (center == topright) ){

        status = (center == 'X') ? 1 : 2;
    }
    
    return status;
}

// Checks for horizontal win, returns corresponding state enum value
int Board::_horiWin(){

    int status = IN_PROGRESS;
    char middle, left, right;
    
    for(int i = 0; i < 3; i++){
        
        middle = boardPosition[i][1];
        
        if(middle == '.'){
            continue;    
        }

        left = boardPosition[i][0];
        right = boardPosition[i][2];
        
        if( (middle == left) && (middle == right) ){
            status = (middle == 'X') ? X_WINS : O_WINS;
            break;   
        }  
    }
    
    return status;    
}

// Checks for vertical win, returns corresponding state enum value
int Board::_vertWin(){

    int status = IN_PROGRESS;
    char middle, top, bottom;
    
    for(int i = 0; i < 3; i++){
        
        middle = boardPosition[1][i];
        
        if(middle == '.'){
            continue;    
        }

        top = boardPosition[0][i];
        bottom = boardPosition[2][i];
        
        if( (middle == top) && (middle == bottom) ){
            status = (middle == 'X') ? X_WINS : O_WINS;
            break;   
        }  
    }
    
    return status;    
}

// Returns false if there is space on the board
bool Board::_isBoardFull(){

    for (int i = 0; i < 3; i++){
        for(int k = 0; k < 3; k++){       
            if (boardPosition[i][k] == '.'){
                return false;
            }
        }          
    }
    return true;
}

/*********************************************************************
** Author: Josh Huff
** Date: December 2, 2016
** Description: Project 10.a -- Board.cpp -- TicTacToe Board class implementation
********************************************************************

#include <iostream>
#include "Board.hpp"

// Constructor -- initializes TicTacToe board with all blank spaces (represented as periods).
Board::Board()
{

    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {       
            boardPosition[i][k] = '.';      
        }
    }
}

********************************************************************
** Description:  Returns false if a space is already occupied.
** Otherwise returns true and sets space to player's piece, all according to respective parameters.
********************************************************************
bool Board::makeMove(int xPos, int yPos, char playerTurn)
{
    // Ensure player pieces are capitals for uniform appearance.
    if (playerTurn == 'o')
    {
        playerTurn == 'O'; 
    }

    if (playerTurn == 'x')
    {
        playerTurn == 'X';
    }

    if (boardPosition[xPos][yPos] != '.')
    {
        return false;
    }

    boardPosition[xPos][yPos] = playerTurn;
    return true;    
}

*******************************************************************
** Description: Uses exhaustive list of win conditions to determine the winner.
** Returns appropriate value based on enum
********************************************************************
State Board::gameState()
{
    if(
       // Horizontal winning positions
       (boardPosition[0][0] == 'X') && (boardPosition[0][1] == 'X') && (boardPosition[0][2] == 'X') ||
       (boardPosition[1][0] == 'X') && (boardPosition[1][1] == 'X') && (boardPosition[1][2] == 'X') ||
       (boardPosition[2][0] == 'X') && (boardPosition[2][1] == 'X') && (boardPosition[2][2] == 'X') ||

       // Vertical winning positions
       (boardPosition[0][0] == 'X') && (boardPosition[1][0] == 'X') && (boardPosition[2][0] == 'X') ||
       (boardPosition[0][1] == 'X') && (boardPosition[1][1] == 'X') && (boardPosition[2][1] == 'X') ||
       (boardPosition[0][2] == 'X') && (boardPosition[1][2] == 'X') && (boardPosition[2][2] == 'X') ||

       // Diagonal winning positions
       (boardPosition[0][0] == 'X') && (boardPosition[1][1] == 'X') && (boardPosition[2][2] == 'X') ||
       (boardPosition[2][0] == 'X') && (boardPosition[1][1] == 'X') && (boardPosition[0][2] == 'X'))
    {
        return X_WINS;
    }

    if(
       // Horizontal winning positions
       (boardPosition[0][0] == 'O') && (boardPosition[0][1] == 'O') && (boardPosition[0][2] == 'O') ||
       (boardPosition[1][0] == 'O') && (boardPosition[1][1] == 'O') && (boardPosition[1][2] == 'O') ||
       (boardPosition[2][0] == 'O') && (boardPosition[2][1] == 'O') && (boardPosition[2][2] == 'O') ||

       // Vertical winning positions
       (boardPosition[0][0] == 'O') && (boardPosition[1][0] == 'O') && (boardPosition[2][0] == 'O') ||
       (boardPosition[0][1] == 'O') && (boardPosition[1][1] == 'O') && (boardPosition[2][1] == 'O') ||
       (boardPosition[0][2] == 'O') && (boardPosition[1][2] == 'O') && (boardPosition[2][2] == 'O') ||

       // Diagonal winning positions
       (boardPosition[0][0] == 'O') && (boardPosition[1][1] == 'O') && (boardPosition[2][2] == 'O') ||
       (boardPosition[2][0] == 'O') && (boardPosition[1][1] == 'O') && (boardPosition[0][2] == 'O'))
    {
        return O_WINS;
    }

    // Board is assumed to be full unless an empty space is located.
    bool isFull = true;
    for (int i = 0; i < 3; i++)
    {
        for (int k = 0; k < 3; k++)
        {       
            if (boardPosition[i][k] == '.')
            {
                isFull = false;      
            }
        } // end of internal loop           
    } // end of external loop

    if (isFull)
    {
        return DRAW;
    }

    // If a win or draw is not determined, the default is that the game is in progress.
    return IN_PROGRESS;
} 

********************************************************************
** Description: Prints a representation of the board, with ordinal numbers to guide future moves.
********************************************************************
void Board::print()
{
    std::cout << "   0   1   2" << std::endl;
    std::cout << " +-----------+" << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << i << "| ";        

        for (int k = 0; k < 3; k++)
        {       
            std::cout << boardPosition[i][k] << " | ";     
        } // end of internal loop

        std::cout << std::endl;
        std::cout << " +-----------+";
        std::cout << std::endl; 
    } // end of external loop    
}
*/

