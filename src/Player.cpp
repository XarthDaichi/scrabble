//
// Created by Xarthy on 0019 October 19, 2022.
//

#include "Player.h"

Player::Player() {
    for (size_t i = 0; i < 6; i++) {
        tiles[i] = ' ';
    }
}

const char *Player::getTiles() const {
    return tiles;
}

std::ostream &operator<<(std::ostream &os, const Player &player) {
    os << "tiles: " << player.tiles;
    return os;
}
