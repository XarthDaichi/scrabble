#include <iostream>
#include "Player.h"
#include "List.h"
#include "Game.h"


int main() {
    srand(time(NULL));
    bool continueQuestion;
    Game game;
    size_t option;

    std::cout << game;
    std::cout << '\n';
    std::cout << "Welcome to Scrabble!" << '\n';
    std::cout << "  1) Start" << '\n';
    std::cout << "  2) Quit" << '\n';
    std::cout << "Select an option: " << '\n'; std::cin >> option;

    do{
        switch (option) {
            case 1:
                int quantityPlayers;
                game.parseDictionary("dictionary.txt");
                std::cout << '\n';
                std::cout << "How many players are there? " << '\n'; std::cin >> quantityPlayers;
                continueQuestion = game.start(quantityPlayers);
                break;
            case 2:
                continueQuestion = false;
                break;
            default:
                std::cout << "Invalid Option. Please insert a valid option: "; std::cin >> option;
        }
    }while(continueQuestion);

    std::cout << "Thanks for playing!" << '\n';

    return 0;
}
