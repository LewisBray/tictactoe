#include "tictactoe.h"

#include <iostream>
#include <vector>
#include <ctime>

using std::cout;
using std::cin;


// Default constructor.
/*
player could be anything (user may want to develop Tic-Tac-Toe modes with
any number of players so we just set to 0.  It's important (at least for
the standard game modes) that the board be filled with blank squares.
*/
tictactoe::tictactoe()
    : player(0)
{
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = BLANK;
}


// Returns the current player.
int tictactoe::GetPlayer() const
{
    return player;
}


// Sets the current player.
void tictactoe::SetPlayer(const int x)
{
    player = x;
}


// Checks if there is a winner in the current game.
/*
This calls helper functions that check whether we have a completed row,
column or diagonal.  The multiple if statements is so that if we get a
true value from any helper function then there is no need to check the
others.

\return     true if there is a winner or false if not.
*/
bool tictactoe::Winner() const
{
    if (RowCheck())
        return true;
    else if (ColCheck())
        return true;
    else if (DiagCheck())
        return true;
    else
        return false;
}


// Displays the board in its current state.
/*
The format may look strange but when this was made it was originally
intended to be scalable for larger game boards (e.g. we could create a
constant called boardSize and this could dictate the width and height
by using it as the limiting value in each of the for loops).
*/
void tictactoe::PrintBoard() const
{
    cout << "\t";
    for (int i = 0; i < 3; ++i)
        printf("   %d   ", i);

    cout << "\n";
    for (int i = 0; i < 3; ++i)
    {
        cout << "\t";
        for (int j = 0; j < 3; ++j)
            cout << " ----- ";

        cout << "\n\t";
        for (int j = 0; j < 3; ++j)
            cout << "|     |";

        printf("\n      %d ", i);
        for (int j = 0; j < 3; ++j)
        {
            char square;
            if (board[i][j] == CROSS)
                square = 'X';
            else if (board[i][j] == NAUGHT)
                square = 'O';
            else
                square = ' ';
            printf("|  %c  |", square);
        }

        cout << "\n\t";
        for (int j = 0; j < 3; ++j)
            cout << "|     |";

        cout << "\n\t";
        for (int j = 0; j < 3; ++j)
            cout << " ----- ";

        cout << "\n\n";
    }
}


// Asks a human player to input a move.
/*
\return     Valid human player move.
*/
move tictactoe::PlayerMove() const
{
    move nextMove;
    while (true)
    {
        cout << "Row: ";
        cin >> nextMove.row;
        cout << "Column: ";
        cin >> nextMove.col;

        if (ValidMove(nextMove))
            break;
    }
    cout << "\n";

    return nextMove;
}


// Returns a random AI move from the remaining available squares.
/*
This is not a very sophisticated AI, it simply picks a random square
from the available squares.  There is no consideration for optimal
moves or trying to combat the player in any way, I'm sure this could
be made much more interesting with some effort.

\return     Valid random AI move.
*/
move tictactoe::RandomAIMove() const
{
    srand((unsigned)time(nullptr));

    // Create a vector of available moves
    std::vector<move> possMoves;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == BLANK)
                possMoves.push_back(move{ i, j });

    // Grab a random one
    int randIndex = rand() % possMoves.size();

    int row = possMoves[randIndex].row;
    int col = possMoves[randIndex].col;
    printf("The AI chose row %d and column %d.\n\n", row, col);

    return possMoves[randIndex];
}


// Updates the board corresponding to the move passed in.
/*
\param  nextMove    Valid move generated since last board update.
*/
void tictactoe::UpdateBoard(const move& nextMove)
{
    int row = nextMove.row;
    int col = nextMove.col;

    board[row][col] = (player == 1) ? CROSS : NAUGHT;
}


// Helper function that checks if a move is valid.
/*
\param  nextMove    Move to check validity of.

\return     true if valid move and false otherwise.
*/
bool tictactoe::ValidMove(const move& nextMove) const
{
    int row = nextMove.row;
    int col = nextMove.col;

    if ((row < 0) || (row > 2) || (col < 0) || (col > 2)) {
        cout << "That is not an available game square!\n";
        return false;
    }

    if ((board[row][col] == CROSS) || (board[row][col] == NAUGHT)) {
        cout << "That square has already been marked!\n";
        return false;
    }

    return true;
}


// Checks if a player has filled in a row.
/*
\return     true if a row has been filled in and false if not.
*/
bool tictactoe::RowCheck() const
{
    // Go through each row
    for (int i = 0; i < 3; ++i)
    {
        // This would need changing for variable board size
        bool rowFilled = (board[i][0] == board[i][1])
                          && (board[i][1] == board[i][2]);

        // If all elements of a row are the
        // same, then make sure they're not blank
        if (rowFilled && (board[i][0] == BLANK))
            rowFilled = false;

        // If passed both tests then we
        // have a legitimate filled row
        if (rowFilled)
            return true;
    }

    // If we got here then no filled rows
    return false;
}


// Checks if a player has filled in a column.
/*
\return     true if a column has been filled in and false if not.
*/
bool tictactoe::ColCheck() const
{
    // Go through each column
    for (int i = 0; i < 3; ++i)
    {
        // This would need changing for variable board size
        bool colFilled = (board[0][i] == board[1][i])
                          && (board[1][i] == board[2][i]);

        // If all elements of a column are the
        // same, then make sure they're not blank
        if (colFilled && (board[0][i] == BLANK))
            colFilled = false;

        // If passed both tests then we
        // have a legitimate filled column
        if (colFilled)
            return true;
    }

    return false;
}


// Checks if a player has filled in a diagonal.
/*
\return     true if a diagonal has been filled in and false if not.
*/
bool tictactoe::DiagCheck() const
{
    // If the middle square is blank then neither
    // diagonal can be filled with non-blank squares
    if (board[1][1] == BLANK)
        return false;

    // Check top-left to bottom-right diagonal
    bool diagFilled = (board[0][0] == board[1][1])
                       && (board[1][1] == board[2][2]);

    // We don't have to check for blank
    // squares thanks to first step
    if (diagFilled)
        return true;

    // If here then move on to checking
    // bottom-left to top-right diagonal
    diagFilled = (board[0][2] == board[1][1])
                  && (board[1][1] == board[2][0]);

    return diagFilled;
}
