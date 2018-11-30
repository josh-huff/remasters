#include <iostream>
#include "Board.hpp"
#include "TicTacToe.hpp"

TicTacToe::TicTacToe(char turn){
    playerTurn = turn;
}

void TicTacToe::play(){

    State state = gameBoard.gameState();
    int xPos, yPos; 
 
    while (state == 0){
        while(true){
        
            xPos = yPos = -1;
            gameBoard.print();
            std::cout << "Player " << playerTurn << "'s move:\n";
            
            std::cin >> xPos >> yPos;

            if(xPos > 2 || yPos > 2 || xPos < 0 || yPos < 0){
                std::cout << "Invalid move.\n";
                continue;
            }else if(gameBoard.makeMove(xPos, yPos, playerTurn)){
                break;
            } else{
                std::cout << "That space is already taken.\n";            
            }
        }
                
        state = gameBoard.gameState();
        playerTurn = (playerTurn == 'X') ? 'O' : 'X';
    }

    std::cout << "The game is over.\n";

    switch(state){
        case 1:
            std::cout << "Player X Wins!\n";
            break;

        case 2:
            std::cout << "Player O Wins!\n";
            break;

        case 3:
            std::cout << "It's a draw!\n";
            break;
    }

    gameBoard.print();
}

int main(){

    std::cout << "Welcome to TicTacToe.\n";

    char playerTurn = ' ';

    while(true){

        std::cout << "Choose which player goes first, X or O: ";
        std::cin >> playerTurn;
        if( playerTurn == 'x' || playerTurn == 'X' || 
            playerTurn == 'o' || playerTurn == 'O'){
            
            break;
        }
        std::cout << "\n";
    }

    if (playerTurn == 'x'){ playerTurn = 'X'; }
    if (playerTurn == 'o'){ playerTurn = 'O'; }

    TicTacToe ttt(playerTurn); 
    ttt.play();
    
    return 0;
}

/*********************************************************************
** Author: Josh Huff
** Date: December 2, 2016
** Description: Project 10.a -- TicTacToe.cpp -- TicTacToe game class implementation
********************************************************************

#include <iostream>
#include "Board.hpp"
#include "TicTacToe.hpp"


TicTacToe::TicTacToe(char turn)
{
    playerTurn = turn;
}

void TicTacToe::play()
{
    State testState = gameBoard.gameState();
    int xPos, yPos; 
    bool validMove = false;
 
    while (testState == 0)
    {
        xPos = yPos = -1; // Resets x and y for each iteration
        gameBoard.print();
        std::cout << "Player " << playerTurn << ": please enter your move." << std::endl;

        while (xPos > 2 || xPos < 0)
        {
            std::cin >> xPos;
        }// End input validation loop X

        while (yPos > 2 || yPos < 0)
        {
            std::cin >> yPos;
        }// End input validation loop Y

        validMove = gameBoard.makeMove(xPos, yPos, playerTurn);

        while (!validMove)
        {
            xPos = yPos = -1;
            std::cout << "That space is already taken. Please select again." << std::endl;
            std::cout << "Player " << playerTurn << ": please enter your move." << std::endl;

            while (xPos > 2 || xPos < 0)
            {
                std::cin >> xPos;
            }// End input validation loop X

            while (yPos > 2 || yPos < 0)
            {
                std::cin >> yPos;
            }// End input validation loop Y

            validMove = gameBoard.makeMove(xPos, yPos, playerTurn);
        }// End input validation - move
        
        testState = gameBoard.gameState();

        switch (playerTurn)
        {
            case 'X':
                playerTurn = 'O';
                break;
 
            case 'O':
                playerTurn = 'X';
                break;
        }// End switch -- changing active player

    }// End main game while loop

    std::cout << "The game is over." << std::endl;

    switch(testState)
    {
        case 1:
            std::cout << "Player X Wins!" << std::endl;
            break;

        case 2:
            std::cout << "Player O Wins!" << std::endl;
            break;

        case 3:
            std::cout << "It's a draw!" << std::endl;
            break;
            
    }// End switch

    gameBoard.print();
}

int main()
{
    std::cout << "Welcome to TicTacToe. " << std::endl
              << "Choose which player goes first, X or O: " << std::endl;

    char input, playerTurn;

    // Special Feature -- input validation and making the X and O capital to make the game prettier
    while (!(input == 'x' || input == 'X' || input == 'o' || input == 'O'))
    {
         std::cin >> input;
    }

    playerTurn = input;

    if (playerTurn == 'x')
    {
        playerTurn = 'X';
    }

    if (playerTurn == 'o')
    {
        playerTurn = 'O';
    }

    TicTacToe ttt(playerTurn); 

    ttt.play();
    
    return 0;
}
*/

