//
// Created by Xarthy on 0019 October 19, 2022.
//

#include "Game.h"

Game::Game(List<char>::listptr (*board)[15], const std::hash_map<std::string, std::string> &dictionary,
           const std::queue<Player> &turnOrder) : board(board), dictionary(dictionary), turn_order(turnOrder) {}

Game::Game() {}

const std::hash_map<std::string, std::string> &Game::getDictionary() const {
    return dictionary;
}

void Game::setDictionary(const std::hash_map<std::string, std::string> &dictionary) {
    Game::dictionary = dictionary;
}

const std::queue<Player> &Game::getTurnOrder() const {
    return turn_order;
}

void Game::setTurnOrder(const std::queue<Player> &turnOrder) {
    turn_order = turnOrder;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "board: " << game.board << " turn_order: " << game.turn_order;
    return os;
}

void Game::parseDictionary(std::string file_name) {
    auto *tmpWord = new std::string;

    std::ifstream file(file_name, std::ios::in);

    if(!file.is_open()){
        throw std::invalid_argument("Could not open the file [" + file_name + "]");
    }

    while(file.good()){
        std::getline(file, *tmpWord, '\n');
        //TODO insert into has map
    }

    file.close();
}


