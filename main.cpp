#include "gamemodes.h"

#include <iostream>


static void displayMenu()
{
    std::cout << "\nMain menu.  Select your game mode:" << std::endl
        << "1) One Player." << std::endl
        << "2) Two player." << std::endl
        << "3) Exit." << std::endl
        << "Choice: ";
}

int main()
{
    std::cout << "Welcome to tic-tac-toe!  You play by entering the row"
        << std::endl << "and column number of the square you want to mark."
        << std::endl;

    bool quit = false;
    while (!quit)
    {
        displayMenu();

        int userChoice;
        std::cin >> userChoice;

        switch (userChoice)
        {
        case 1:
            onePlayerGame();
            break;
        case 2:
            twoPlayerGame();
            break;
        case 3:
            std::cout << std::endl << "Thanks for playing!!!" << std::endl;
            quit = true;
            break;
        default:
            std::cout << "Invalid choice, please choose again." << std::endl;
            break;
        }
    }

    return 0;
}
