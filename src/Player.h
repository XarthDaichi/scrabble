//
// Created by Xarthy on 0019 October 19, 2022.
//

#ifndef SCRABBLE_PLAYER_H
#define SCRABBLE_PLAYER_H


#include <ostream>

class Player {
private:
    int number;
    char tiles[6]{};
public:
    Player();

    char *getTiles();

    int getNumber() const;

    void setNumber(int number);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    char operator[](int position);
};


#endif //SCRABBLE_PLAYER_H
