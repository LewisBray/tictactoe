#ifndef __TICTACTOE_H__
#define __TICTACTOE_H__

// Struct for holding the coordinates of a player's move.
struct Move
{
    Move() {}
    Move(const int row, const int col) : row_{ row }, col_{ col } {}

    int row_;
    int col_;
};

// Class to provide methods for making game modes of tic-tac-toe.
class TicTacToe
{
public:
    enum { BoardSize = 3 };

    TicTacToe();

    int getPlayer() const;
    bool playerHasWon() const;
    void displayBoard() const;
    void setPlayer(const int nextPlayer);
    void updateBoard(const Move& nextMove);
    Move generateRandomAIMove() const;
    Move askHumanPlayerForMove() const;

private:
    enum class SquareState { Blank, Cross, Naught };

    int player_;
    SquareState board_[BoardSize][BoardSize];

    char squareStateToChar(const int row, const int col) const;
    bool playerHasWonByRow() const;
    bool playerHasWonByColumn() const;
    bool playerHasWonByDiagonal() const;
    bool moveIsValid(const Move& move) const;
    void drawRowOfSquares(const int row) const;
};

#endif
