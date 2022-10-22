#include <iostream>
#include "Player.h"
#include "List.h"
#include "Game.h"
int main() {


    //initializing random
    srand(time(NULL));

    Game game;
    game.parseDictionary("dictionary.txt");
    for (auto i : game.getDictionary()) {
        // Para revisar como sirve pairs usamos: https://www.geeksforgeeks.org/pair-in-cpp-stl/
        std::cout << i.first << '\n';
    }
    return 0;
}
