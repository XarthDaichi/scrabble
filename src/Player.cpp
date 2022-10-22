//
// Created by Xarthy on 0019 October 19, 2022.
//

#include <iostream>
#include "Player.h"

Player::Player() {
    for (size_t i = 0; i < 6; i++) {
        tiles[i] = ' ';
    }
}

char *Player::getTiles() {
    return tiles;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "tiles: " << player.tiles;
    return os;
}

char Player::operator[](int position) {
    try {
        return tiles[position];
    } catch (std::bad_alloc exception) {
        std::clog << "Position is outside of vector length, enter a value between 0-5";
    }
}

int Player::getNumber() const {
    return number;
}

void Player::setNumber(int number) {
    Player::number = number;
}
