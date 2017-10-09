#include <iostream>

#include "gamemodes.h"

using namespace std;

int main()
{
    cout << "Welcome to tic-tac-toe!  You play by entering the row and column number of the square you want to mark." << endl;

    bool quit = false;

    while(!quit)
    {
        int choice;

        cout << endl << "Main menu.  Select your game mode:" << endl;
        cout << "1) One Player." << endl;
        cout << "2) Two player." << endl;
        cout << "3) Exit." << endl;
        cout << "Choice: ";
        cin >> choice;

        if(choice > 3 || choice < 1){cout << "Invalid choice." << endl;}
        else
        {
            switch(choice)
            {
                case 1: one_player_game();
                        break;
                case 2: two_player_game();
                        break;
                case 3: cout << endl << "Thanks for playing!!!" << endl;
                        quit = true;
                        break;
            }
        }
    }

    return 0;
}
