#include "tictactoe.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <chrono>


TicTacToe::TicTacToe()
    : player_{ 0 }
{
    // It's important (at least for the standard game modes) that the board be
    // filled with blank states as this fact is used when checking for a winner.
    for (int row = 0; row < BoardSize; ++row)
        for (int col = 0; col < BoardSize; ++col)
            board_[row][col] = SquareState::Blank;
}

int TicTacToe::getPlayer() const
{
    return player_;
}

void TicTacToe::setPlayer(const int nextPlayer)
{
    player_ = nextPlayer;
}

bool TicTacToe::playerHasWon() const
{
    return playerHasWonByRow()
        || playerHasWonByColumn()
        || playerHasWonByDiagonal();
}

// The format may look strange for this drawing process but when this was made
// it was originally intended to be scalable for larger game boards.
void TicTacToe::displayBoard() const
{
    std::cout << '\t';
    for (int row = 0; row < BoardSize; ++row)
        std::cout << std::setw(4) << row << std::setw(3) << ' ';

    std::cout << '\n';
    for (int row = 0; row < BoardSize; ++row)
        drawRowOfSquares(row);
}

void TicTacToe::drawRowOfSquares(const int row) const
{
    std::cout << '\t' << std::setfill('-');
    for (int col = 0; col < BoardSize; ++col)
        std::cout << ' ' << std::setw(6) << ' ';

    std::cout << std::setfill(' ') << "\n\t";
    for (int col = 0; col < BoardSize; ++col)
        std::cout << '|' << std::setw(6) << '|';

    std::cout << '\n' << std::setw(7) << row << ' ';
    for (int col = 0; col < BoardSize; ++col) {
        const char squareState = squareStateToChar(row, col);
        std::cout << '|' << std::setw(3) << squareState << std::setw(3) << '|';
    }

    std::cout << "\n\t";
    for (int col = 0; col < BoardSize; ++col)
        std::cout << '|' << std::setw(6) << '|';

    std::cout << "\n\t" << std::setfill('-');
    for (int col = 0; col < BoardSize; ++col)
        std::cout << ' ' << std::setw(6) << ' ';

    std::cout << std::setfill(' ') << std::endl;
}

char TicTacToe::squareStateToChar(const int row, const int col) const
{
    if (board_[row][col] == SquareState::Cross)
        return 'X';
    else if (board_[row][col] == SquareState::Naught)
        return 'O';
    else
        return ' ';
}

Move TicTacToe::askHumanPlayerForMove() const
{
    while (true)
    {
        Move nextMove;
        std::cout << "Row: ";
        std::cin >> nextMove.row_;
        std::cout << "Column: ";
        std::cin >> nextMove.col_;

        if (moveIsValid(nextMove)) {
            std::cout << std::endl;
            return nextMove;
        }
    }
}

// This is not a very sophisticated AI, it simply picks a random square from the
// available squares.  There is no consideration for optimal moves or trying to
// combat the player in any way, I'm sure this could be made much more
// interesting with some effort.
Move TicTacToe::generateRandomAIMove() const
{
    std::vector<Move> possibleMoves;
    for (int row = 0; row < BoardSize; ++row)
        for (int col = 0; col < BoardSize; ++col)
            if (board_[row][col] == SquareState::Blank)
                possibleMoves.emplace_back(row, col);

    const int randIndex = generateRandomIndex(possibleMoves.size() - 1);

    const int randomRow = possibleMoves[randIndex].row_;
    const int randomCol = possibleMoves[randIndex].col_;
    std::cout << "The AI chose row " << randomRow
        << " and column " << randomCol << ".\n" << std::endl;

    return possibleMoves[randIndex];
}

//nextMove here has to be valid as determined by TicTacToe::moveIsValid.
void TicTacToe::updateBoard(const Move& nextMove)
{
    const int row = nextMove.row_;
    const int col = nextMove.col_;

    board_[row][col] = (player_ == 1) ?
        SquareState::Cross : SquareState::Naught;
}

bool TicTacToe::moveIsValid(const Move& move) const
{
    const int row = move.row_;
    const int col = move.col_;

    if (row < 0 || row > BoardSize - 1 || col < 0 || col > BoardSize - 1) {
        std::cout << "That is not an available game square!" << std::endl;
        return false;
    }

    if (board_[row][col] == SquareState::Cross
        || board_[row][col] == SquareState::Naught) {
        std::cout << "That square has already been marked!" << std::endl;
        return false;
    }

    return true;
}

bool TicTacToe::playerHasWonByRow() const
{
    for (int row = 0; row < BoardSize; ++row)
    {
        const bool rowFilledWithSameState = std::invoke([row, this]() {
            for (int col = 0; col < BoardSize - 1; ++col)
                if (board_[row][col] != board_[row][col + 1])
                    return false;

            return true;
        });

        if (rowFilledWithSameState) {
            const bool rowIsNotBlank = (board_[row][0] != SquareState::Blank);
            if (rowIsNotBlank)
                return true;
        }
    }

    return false;
}

bool TicTacToe::playerHasWonByColumn() const
{
    for (int col = 0; col < BoardSize; ++col)
    {
        const bool colFilledWithSameState = std::invoke([col, this]() {
            for (int row = 0; row < BoardSize - 1; ++row)
                if (board_[row][col] != board_[row + 1][col])
                    return false;

            return true;
        });

        if (colFilledWithSameState) {
            const bool colIsNotBlank = (board_[0][col] != SquareState::Blank);
            if (colIsNotBlank)
                return true;
        }
    }

    return false;
}

bool TicTacToe::playerHasWonByDiagonal() const
{
    if (board_[1][1] == SquareState::Blank) // If middle square blank neither...
        return false;                       // ...diagonal can be non-blank

    // Check top-left to bottom-right diagonal is filled with same state
    const bool tlbrDiagFilledWithSameState = std::invoke([this]() {
        for (int i = 0; i < BoardSize - 1; ++i)
            if (board_[i][i] != board_[i + 1][i + 1])
                return false;

        return true;
    });

    if (tlbrDiagFilledWithSameState)    // No need to check for blank...
        return true;                    // ... squares thanks to first step

    // If here, check bottom-left to top-right diagonal
    const bool bltrDiagFilledWithSameState = std::invoke([this]() {
        for (int i = 0; i < BoardSize - 1; ++i)
            if (board_[BoardSize - 1 - i][i] != board_[BoardSize - 2 - i][i + 1])
                return false;

        return true;
    });

    return bltrDiagFilledWithSameState;
}

// Generates a number in the range [low, high]
int TicTacToe::generateRandomIndex(const int lastIndex)
{
    std::uniform_int_distribution uniformDist{ 0, lastIndex };

    const auto currentTime = std::chrono::system_clock::now();
    const unsigned rngSeed =
        static_cast<unsigned>(currentTime.time_since_epoch().count());

    std::minstd_rand rng{ rngSeed };

    return uniformDist(rng);
}
