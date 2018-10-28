#include "tictactoe.h"

#include <iostream>


static bool askUserToPlayAgain()
{
    std::cout << std::endl
        << "Would you like to play again? (Y/N)" << std::endl;

    while (true)
    {
        char userChoice;
        std::cin >> userChoice;

        if (userChoice == 'N' || userChoice == 'n')
            return false;
        else if (userChoice == 'Y' || userChoice == 'y')
            return true;
        else
            std::cout << "Invalid choice, please select from Y/N: ";
    }
}

enum TurnOrder { First = 1, Second = 2 };

static TurnOrder askHumanForTurnOrder()
{
    std::cout << "Would you like to play first or second?  ";

    while (true)
    {
        std::cout << "Enter 1 for first or 2 for second: ";

        int turnChoice;
        std::cin >> turnChoice;

        if (turnChoice == 1)
            return TurnOrder::First;
        else if (turnChoice == 2)
            return TurnOrder::Second;
        else
            std::cout << "Invalid choice.  ";
    }
    std::cout << std::endl;
}

void onePlayerGame()
{
    do
    {
        const TurnOrder humanTurn = askHumanForTurnOrder();

        TicTacToe game;

        if (humanTurn == TurnOrder::First)  // AI doesn't need to see the
            game.displayBoard();            // board to make its first move

        constexpr int maxNumTurns = TicTacToe::BoardSize * TicTacToe::BoardSize;
        for (int turn = 1; turn <= maxNumTurns; ++turn)
        {
            game.setPlayer((turn - 1) % 2 + 1);

            const Move nextMove = std::invoke([&game, humanTurn]() {
                if (game.getPlayer() == humanTurn) {
                    std::cout << "Your turn." << std::endl;
                    return game.askHumanPlayerForMove();
                }
                else {
                    std::cout << "AI's turn." << std::endl;
                    return game.generateRandomAIMove();
                }
            });

            game.updateBoard(nextMove);

            game.displayBoard();

            if (game.playerHasWon())
            {
                if (game.getPlayer() == humanTurn)
                    std::cout << "You win!!!";
                else
                    std::cout << "The AI wins...";
                break;
            }

            if (turn == maxNumTurns)
                std::cout << "No more moves remaining.  It's a draw!!!";

            std::cout << std::endl;
        }
    } while (askUserToPlayAgain());
}

void twoPlayerGame()
{
    do
    {
        TicTacToe game;

        std::cout << std::endl;
        game.displayBoard();

        constexpr int maxNumTurns = TicTacToe::BoardSize * TicTacToe::BoardSize;
        for (int turn = 1; turn < maxNumTurns; ++turn)
        {
            game.setPlayer((turn - 1) % 2 + 1);

            std::cout << "Player " << game.getPlayer()
                << "'s turn." << std::endl;

            const Move nextMove = game.askHumanPlayerForMove();
            game.updateBoard(nextMove);
            game.displayBoard();

            if (game.playerHasWon()) {
                std::cout << "Player " << game.getPlayer() << " wins!!!";
                break;
            }

            if (turn == maxNumTurns)
                std::cout << "No more moves remaining.  It's a draw!!!";
        }
    } while (askUserToPlayAgain());
}
