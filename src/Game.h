#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H
#include "List.h"
#include "Player.h"
#include "enum.h"
#include <Windows.h>
#include <vector>
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

class Game {
private:
    List<char>::listptr board[11][11]; // Node * board[10][10]
    std::map<std::string, bool> dictionary;
    std::queue<Player*> turnOrder;
    std::vector<char> letters = {'a','e','i','o','u','c','h','b','d','s','l','p','t','j','m'};

public:
    Game();

    const std::map<std::string, bool> &getDictionary() const;

    void setDictionary(const std::map<std::string, bool> &dictionary);

    const std::queue<Player*> &getTurnOrder() const;

    void setTurnOrder(const std::queue<Player*> &turnOrder);

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void parseDictionary(std::string fileName);

    std::string parseWord(List<char>::listptr, Direction direction);

    bool start(int playerAmount);

    bool end(Player& player);

    bool verifyBoard();

    bool insertWord(std::string palabra, int x, int y, Direction direction,  bool firstTurn);

    int verifyIntersection(const std::string& palabra, int x, int y);

    Player* determineTie(std::queue<Player*> players);

    bool runGame();
};


#endif //SCRABBLE_GAME_H
