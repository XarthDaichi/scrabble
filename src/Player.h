//
// Created by Xarthy on 0019 October 19, 2022.
//

#ifndef SCRABBLE_PLAYER_H
#define SCRABBLE_PLAYER_H


#include <ostream>

class Player {
private:
    char tiles[6];
public:
    Player();
    Player(char *tiles);

    const char *getTiles() const;

    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    char operator[](int position);
};


#endif //SCRABBLE_PLAYER_H
