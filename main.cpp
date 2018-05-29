#include "gamemodes.h"

#include <iostream>

using std::cout;
using std::cin;


int main()
{
    cout << "Welcome to tic-tac-toe!  You play by entering the row\n";
    cout << "and column number of the square you want to mark.\n";

    bool quit = false;
    while (!quit)
    {
        int choice;
        cout << "\nMain menu.  Select your game mode:\n";
        cout << "1) One Player.\n";
        cout << "2) Two player.\n";
        cout << "3) Exit.\n";
        cout << "Choice: ";
        cin >> choice;

        if ((choice > 3) || (choice < 1))
            cout << "Invalid choice.\n";
        else
        {
            switch (choice)
            {
            case 1:
                OnePlayerGame();
                break;
            case 2:
                TwoPlayerGame();
                break;
            case 3:
                cout << "\nThanks for playing!!!\n";
                quit = true;
                break;
            }
        }
    }

    return 0;
}
