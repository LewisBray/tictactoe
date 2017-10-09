#include <iostream>

#include "tictactoe.h"

using namespace std;

bool play_again()
{
    char choice;

    cout << endl << "Would you like to play again? (Y/N)" << endl;

    while(1)
    {
        cin >> choice;

        if(choice == 'N' || choice == 'n'){return false;}
        else if(choice == 'Y' || choice == 'y'){return true;}
        else{cout << "Invalid choice, please select from Y/N: ";}
    }
}

void one_player_game()
{
    int player_turn;

    while(1)
    {
        cout << "Would you like to play first or second?  ";

        while(1)
        {
            cout << "Enter 1 for first or 2 for second: ";
            cin >> player_turn;

            if(player_turn == 1 || player_turn == 2){break;}
            else{cout << "Invalid choice.  ";}
        }

        cout << endl;

        tictactoe game;

        if(player_turn == 1){game.print_board();}

        for(int i = 0; i < 9; i++)
        {
            int row, column;

            game.set_player(i%2 + 1);

            if(game.get_player() == player_turn)
            {
                cout << "Your turn." << endl;

                game.get_move(row, column);
            }
            else
            {
                cout << "AI's turn." << endl;

                game.random_ai_move(row, column);
            }

            game.update_board(row, column);

            game.print_board();

            if(game.winner())
            {
                if(game.get_player() == player_turn){cout << "You win!!!";}
                else{cout << "The AI wins...";}

                break;
            }

            if(i == 8){cout << "No more moves remaining.  It's a draw!!!";}
        }

        if(!play_again()){break;}
    }
}

void two_player_game()
{
    while(1)
    {
        cout << endl;

        tictactoe game;

        game.print_board();

        for(int i = 0; i < 9; i++)
        {
            int row, column;

            game.set_player(i%2 + 1);

            cout << "Player " << game.get_player() << "'s turn." << endl;

            game.get_move(row, column);

            game.update_board(row, column);

            game.print_board();

            if(game.winner())
            {
                cout << "Player " << game.get_player() << " wins!!!";
                break;
            }

            if(i == 8){cout << "No more moves remaining.  It's a draw!!!";}
        }

        if(!play_again()){break;}
    }
}
