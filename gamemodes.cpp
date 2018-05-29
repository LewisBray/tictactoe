#include "tictactoe.h"

#include <iostream>

using std::cout;
using std::cin;


// Functions providing game modes using the tictactoe class methods.

// Loops until player enters a valid choice of whether they want to play again.
bool PlayAgain()
{
    cout << "\nWould you like to play again? (Y/N)\n";

    char choice;
    while (true)
    {
        cin >> choice;

        if ((choice == 'N') || (choice == 'n'))
            return false;
        else if ((choice == 'Y') || (choice == 'y'))
            return true;
        else
            cout << "Invalid choice, please select from Y/N: ";
    }
}


// One player game of human against an (incredibly dumb) AI.
void OnePlayerGame()
{
    // Loop until player doesn't want to play anymore
    while (true)
    {
        // Game setup
        cout << "Would you like to play first or second?  ";

        int playerTurn;
        while (true)    // Get valid turn order for human player
        {
            cout << "Enter 1 for first or 2 for second: ";
            cin >> playerTurn;

            if ((playerTurn == 1) || (playerTurn == 2))
                break;
            else
                cout << "Invalid choice.  ";
        }
        cout << "\n";


        tictactoe game;

        if (playerTurn == 1)    // AI doesn't need to see the
            game.PrintBoard();  // board to make its first move

        // Main game loop (max 9 moves)
        for (int i = 0; i < 9; ++i)
        {
            game.SetPlayer((i % 2) + 1);

            // Get next move from human/AI
            move nextMove;
            if (game.GetPlayer() == playerTurn) {
                cout << "Your turn.\n";
                nextMove = game.PlayerMove();
            }
            else {
                cout << "AI's turn.\n";
                nextMove = game.RandomAIMove();
            }

            game.UpdateBoard(nextMove);

            game.PrintBoard();

            if (game.Winner())
            {
                if (game.GetPlayer() == playerTurn)
                    cout << "You win!!!";
                else
                    cout << "The AI wins...";
                break;
            }

            if (i == 8)
                cout << "No more moves remaining.  It's a draw!!!";
        }

        if (!PlayAgain())
            break;
    }
}


// Standard two-player game of Tic-Tac-Toe.
void TwoPlayerGame()
{
    // Loop until players don't want to play anymore
    while (true)
    {
        tictactoe game;

        cout << "\n";
        game.PrintBoard();

        // Main game loop (max 9 turns)
        for (int i = 0; i < 9; ++i)
        {
            game.SetPlayer((i % 2) + 1);

            printf("Player %d's turn.\n", game.GetPlayer());

            move nextMove = game.PlayerMove();

            game.UpdateBoard(nextMove);

            game.PrintBoard();

            if (game.Winner()) {
                printf("Player %d wins!!!", game.GetPlayer());
                break;
            }

            if (i == 8)
                cout << "No more moves remaining.  It's a draw!!!";
        }

        if (!PlayAgain())
            break;
    }
}
