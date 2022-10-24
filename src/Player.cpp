//
// Created by Xarthy on 0019 October 19, 2022.
//

#include <iostream>
#include "Player.h"

Player::Player() {}

std::vector<char> &Player::getTiles(){
    return tiles;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << player.name << ": tiles: ";
    for (auto i: player.tiles) { os << i << ' | '; }
    return os;
}

char Player::operator[](int position) {
    try {
        return tiles[position];
    } catch (std::bad_alloc exception) {
        std::clog << "Position is outside of vector length, enter a value between 0-5";
    }
}

std::string Player::getName() const {
    return name;
}

void Player::setName(std::string name) {
    Player::name = name;
}
