//
// Created by Xarthy on 0019 October 19, 2022.
//

#include "Game.h"

Game::Game() {}

const std::map<std::string, bool> &Game::getDictionary() const {
    return dictionary;
}

void Game::setDictionary(const std::map<std::string, bool> &dictionary) {
    Game::dictionary = dictionary;
}

const std::queue<Player> &Game::getTurnOrder() const {
    return turn_order;
}

void Game::setTurnOrder(const std::queue<Player> &turnOrder) {
    turn_order = turnOrder;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "board: " << game.board << " turn_order: " << game.turn_order.size();
    return os;
}

void Game::parseDictionary(std::string file_name) {
    std::string tmpWord;

    std::ifstream file(file_name, std::ios::in);

    if(!file.is_open()){
        throw std::invalid_argument("Could not open the file [" + file_name + "]");
    }

    while(file.good()){
        getline(file, tmpWord, '\n');
        dictionary[tmpWord] = true;
    }

    file.close();
}

void Game::start(int player_amount) {
    std::vector<Player> player_selection_vector;
    for (int i = 0; i < player_amount; i++) {
        player_selection_vector.push_back(Player());
        for (int j = 0; j < 6; i++) {
            player_selection_vector[i].getTiles()[j] = 'a' + rand()%26;
        }
    }
    for (int i = player_amount; i >= 0; i--) {
        int num = rand()%i;
        turn_order.push(player_selection_vector[num]);
        player_selection_vector.erase(player_selection_vector.begin() + num);
    }
}

void Game::end() {

}

void Game::turn() {

}

bool Game::verify() {
    return false;
}


