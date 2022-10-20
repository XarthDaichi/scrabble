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
public:
    Game();

    Game(List<char>::listptr (*board)[15], const std::hash_map<std::string, std::string> &dictionary,
         const std::queue<Player> &turnOrder);

    const std::hash_map<std::string, std::string> &getDictionary() const;

    void setDictionary(const std::hash_map<std::string, std::string> &dictionary);

    const std::queue<Player> &getTurnOrder() const;

    void setTurnOrder(const std::queue<Player> &turnOrder);

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void parseDictionary(std::string file_name);


};


#endif //SCRABBLE_GAME_H
