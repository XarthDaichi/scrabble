//
// Created by Xarthy on 0019 October 19, 2022.
//

#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H
#include "List.h"
#include "Player.h"
#include <queue>
#include <hash_map>
#include <ostream>

class Game {
private:
    List<char>::listptr board[15][15];
    std::hash_map<std::string, std::string> dictionary;
    std::queue<Player> turn_order;
    int tile_amount[6] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6, 4, 6, 4, 2, 2, 1, 2, 1};
public:
    Game();

    const std::hash_map<std::string, std::string> &getDictionary() const;

    void setDictionary(const std::hash_map<std::string, std::string> &dictionary);

    const std::queue<Player> &getTurnOrder() const;

    void setTurnOrder(const std::queue<Player> &turnOrder);

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void parseDictionary(std::string file_name);

    void start(int player_amount);

    void end();

    bool verify();

    bool verify_right();

    bool verify_left();

    void draw_tiles(int amount);
};


#endif //SCRABBLE_GAME_H
