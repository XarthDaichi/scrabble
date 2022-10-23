#include <iostream>
#include "Player.h"
#include "List.h"
#include "Game.h"
int main() {


    //initializing random
    srand(time(NULL));

    Game game;
    game.parseDictionary("dictionary.txt");

    // this is verifying that the parsing works
//    for (auto i : game.getDictionary()) {
//        // Para revisar como sirve pairs usamos: https://www.geeksforgeeks.org/pair-in-cpp-stl/
//        std::cout << i.first << '\n';
//    }

    std::cout << game << '\n';
    game.board[0][0]->value = 'a';
    std::cout << game << '\n';
    return 0;
}
