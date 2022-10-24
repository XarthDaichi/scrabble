#include <iostream>
#include "Player.h"
#include "List.h"
#include "Game.h"


int main() {
    //initializing random
    srand(time(NULL));
    size_t option;
    Game game;

    std::cout << game;
    std::cout << '\n';
    std::cout << "Welcome to Scrabble!" << '\n';
    std::cout << "  1) Start" << '\n';
    std::cout << "  2) Quit" << '\n';
    std::cout << "Select an option: " << '\n'; std::cin >> option;

    switch (option) {
        case 1:
            int quantityPlayers;
            game.parseDictionary("dictionary.txt");
            std::cout << '\n';
            std::cout << "How many players are there? " << '\n'; std::cin >> quantityPlayers;
            game.start(quantityPlayers);
            break;
        case 2:
            break;
        default:
            std::cout << "Invalid number." << '\n';
    }


//    std::map<std::string, bool> test;
//    test["something"] = true;
//    std::cout << test["other"]; si da negativo
    return 0;
}
