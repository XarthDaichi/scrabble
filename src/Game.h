//
// Created by Xarthy on 0019 October 19, 2022.
//

#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H
#include "List.h"
#include "Player.h"
#include <queue>
// Para verificar algunas cosas de los mapas usamos: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
#include <map>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>

// Consulted https://cplusplus.com/reference/cstdlib/rand/ for random
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

struct Game {
    List<char>::listptr board[10][10]; // Node * board[10][10]
    std::map<std::string, bool> dictionary;
    std::queue<Player> turn_order;
    int tile_amount[26] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1};

    Game();

    const std::map<std::string, bool> &getDictionary() const;

    void setDictionary(const std::map<std::string, bool> &dictionary);

    const std::queue<Player> &getTurnOrder() const;

    void setTurnOrder(const std::queue<Player> &turnOrder);

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void parseDictionary(std::string file_name);

    void start(int player_amount);

    bool end(Player& player);

    void turn();

    bool verify();

    bool winConditions(Player& currentPlayer);

//    void draw_tiles(int amount);
};


#endif //SCRABBLE_GAME_H
