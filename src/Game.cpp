//
// Created by Xarthy on 0019 October 19, 2022.
//

#include "Game.h"

Game::Game() {
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            board[i][j] = new Node<char>(' ');
        }
    }
}

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
    os << "board: \n";
    for (size_t i = 0; i < 10; i++) {
        os << " _ _ _ _ _ _ _ _ _ _\n|";
        for (size_t j = 0; j < 10; j++) {
            os << game.board[i][j]->value << "|";
        }
        os << '\n';
    }
    os << " _ _ _ _ _ _ _ _ _ \n";
    os << " turn_order: " << game.turn_order.size();
    return os;
}

void Game::parseDictionary(std::string fileName) {
    std::string tmpWord;

    std::ifstream file(fileName, std::ios::in);

    if(!file.is_open()){
        throw std::invalid_argument("Could not open the file [" + fileName + "]");
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
        for (int j = 0; j < 6; j++) {
            player_selection_vector[i].getTiles()[j] = 'a' + rand()%26;
            player_selection_vector[i].setNumber(i+1);
        }
    }
    for (int i = player_amount; i >= 0; i--) {
        int num = rand()%i;
        turn_order.push(player_selection_vector[num]);
        player_selection_vector.erase(player_selection_vector.begin() + num);
    }
}

bool Game::end(Player& player) {
    std::cout << "Congratulations player " << player.getNumber() << "!!!\n";
    std::cout << "You win!!!\n\n";
    std::cout << "Play again (1 for yes | 0 for no): ";
    int selection;
    std::cin >> selection;
    return selection != 0;
}

void Game::turn() {
    /*
     * do {
     *
     * } while(!verify)
     */
}

bool Game::winConditions(Player& currentPlayer) {
    /*
     *  verificar que el jugador ya no tiene letras
     *  no tiene posibilidad de hacer ninguna otra palabra, gana el que tiene la menor cantidad de letras
     *  si los ultimos dos son falsos gana el que tenga la suma de letras menor, hacer por ASCII
     */
    return false;
}

bool Game::verify() {
    // verify that the whole matrix has no invalid words
    return false;
}

