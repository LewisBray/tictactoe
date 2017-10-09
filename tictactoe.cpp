#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tictactoe.h"

using namespace std;

tictactoe::tictactoe() : player(0)
{
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            board[i][j] = M_B;
        }
    }
}

int tictactoe::get_player()
{
    return player;
}

void tictactoe::set_player(int x)
{
    player = x;
}

bool tictactoe::winner()
{
    return (row_check() || col_check() || diag_check());
}

void tictactoe::print_board()
{
    cout << "\t";
    for(int i = 0; i < 3; i++)
    {
        cout << "   " << i << "   ";
    }
    cout << endl;
    for(int i = 0; i < 3; i++)
        {
        cout << "\t";
        for(int j = 0; j < 3; j++)
        {
            cout << " ----- ";
        }
        cout << endl << "\t";
        for(int j = 0; j < 3; j++)
        {
            cout << "|     |";
        }
        cout << endl << "      " << i << " ";
        for(int j = 0; j < 3; j++)
        {
            cout << "|  ";
            if(board[i][j] == M_X){cout << 'X';}
            else if(board[i][j] == M_O){cout << 'O';}
            else{cout << ' ';}
            cout << "  |";
        }
        cout << endl << "\t";
        for(int j = 0; j < 3; j++)
        {
            cout << "|     |";
        }
        cout << endl << "\t";
        for(int j = 0; j < 3; j++)
        {
            cout << " ----- ";
        }
        cout << endl << endl;
    }
}

void tictactoe::get_move(int& row, int& column)
{
    while(1)
    {
        cout << "Row: ";
        cin >> row;
        cout << "Column: ";
        cin >> column;

        if(valid(row, column))
        {
            cout << endl;
            break;
        }
    }
}

void tictactoe::random_ai_move(int& row, int& column)
{
    srand(time(NULL));

    while(1)
    {
        int x = rand()%3;
        int y = rand()%3;

        if(board[x][y] == M_B)
        {
            cout << "The AI chose row " << x << " and column " << y << "." << endl << endl;
            row = x;
            column = y;
            break;
        }
    }
}

void tictactoe::update_board(int row, int column)
{
    if(player == 1){board[row][column] = M_X;}

    if(player == 2){board[row][column] = M_O;}
}

bool tictactoe::valid(int row, int column)
{
    if(row < 0 || row > 2 || column < 0 || column > 2)
    {
        cout << "That is not an available game square!" << endl;
        return false;
    }

    if(board[row][column] == M_X || board[row][column] == M_O)
    {
        cout << "That square has already been marked!" << endl;
        return false;
    }

    return true;
}

bool tictactoe::row_check()
{
    for(int i = 0; i < 3; i++)
    {
        if(board[i][0] != M_B && board[i][1] != M_B && board[i][2] != M_B &&
           board[i][0] == board[i][1] && board[i][1] == board[i][2]){return true;}
    }

    return false;
}

bool tictactoe::col_check()
{
    for(int i = 0; i < 3; i++)
    {
        if(board[0][i] != M_B && board[1][i] != M_B && board[2][i] != M_B &&
           board[0][i] == board[1][i] && board[1][i] == board[2][i]){return true;}
    }

    return false;
}

bool tictactoe::diag_check()
{
    if(board[0][0] != M_B && board[1][1] != M_B && board[2][2] != M_B &&
       board[0][0] == board[1][1] && board[1][1] == board[2][2]){return true;}

    if(board[0][2] != M_B && board[1][1] != M_B && board[2][0] != M_B &&
       board[0][2] == board[1][1] && board[1][1] == board[2][0]){return true;}

    return false;
}
