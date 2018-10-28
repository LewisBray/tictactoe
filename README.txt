This is a simple tic-tac-toe program.  Learning programming from 'Jumping Into
C++' by Alex Allain there is a repeated idea of learning new topics by writing
code for a tic-tac-toe game.  This is just my most updated version of the code
worked on throughout reading the book that has been expanded upon and modified
with new things I learn about the C++ language.

The data and methods needed for writing a game loop are put into a class called
TicTacToe and two simple game modes of a standard two player game and a single
player game against an AI picking squares at random were included.

This has now been updated to the state where I believe the logic is scaleable to
have different size boards determined at runtime.  Things that would have to
change would be the game board needs to be replaced by a vector of vectors and
the board size can no longer be an enum declared in the TicTacToe class.
