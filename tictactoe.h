#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__


// The different states a square on the board can be in.
enum state {BLANK, CROSS, NAUGHT};


// Struct for holding the coordinates of a player's move.
struct move
{
    int row;
    int col;
};


// Class to provide methods for making game modes of tic-tac-toe.
class tictactoe
{
public:
    tictactoe();

    int GetPlayer() const;
    bool Winner() const;
    void SetPlayer(const int x);
    void PrintBoard() const;
    void UpdateBoard(const move& nextMove);
    move PlayerMove() const;
    move RandomAIMove() const;

private:
    int player;             // Current player (typically 1 or 2)
    state board[3][3];      // Holds state of every board square

    bool RowCheck() const;
    bool ColCheck() const;
    bool DiagCheck() const;
    bool ValidMove(const move& nextMove) const;
};

#endif
