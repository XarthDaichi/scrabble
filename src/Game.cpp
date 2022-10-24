//
// Created by Xarthy on 0019 October 19, 2022.
//

#include "Game.h"

Game::Game() {
    for (size_t i = 0; i < 11; i++) {
        for (size_t j = 0; j < 11; j++) {
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

const std::queue<Player*> &Game::getTurnOrder() const {
    return turnOrder;
}

void Game::setTurnOrder(const std::queue<Player*> &turnOrder) {
    this->turnOrder = turnOrder;
}

std::ostream &operator<<(std::ostream &os, const Game &game) {
    os << "       0     1     2     3     4     5     6     7     8     9     10\n";
    for (size_t i = 0; i < 11; i++) {
        os << "      -----------------------------------------------------------------\n";
        os << i;
        if (i <10) os << "    | ";
        else os << "   | ";
        for (size_t j = 0; j < 11; j++) {
            os << "  " << game.board[i][j]->value << " | ";
        }
        os << '\n';
    }
    os << "      -----------------------------------------------------------------\n";
    if (!game.turnOrder.empty()) os << " Turn: " << game.turnOrder.front();
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

void Game::start(int playerAmount) {
    std::vector<Player*> playerSelectionVector;
    std::string tempName;
    for (int i = 0; i < playerAmount; i++) {
        playerSelectionVector.push_back(new Player());
        std::cout << "Enter your name: ";
        std::cin >> tempName;
        playerSelectionVector.at(i)->setName(tempName);
        for (int j = 0; j < 6; j++) {
            playerSelectionVector.at(i)->getTiles().push_back('a' + rand()%26);
        }
    }
    for (int i = playerAmount; i > 0; i--) {
        int num = rand()%i;
        turnOrder.push(playerSelectionVector[num]);
        playerSelectionVector.erase(playerSelectionVector.begin() + num);
    }

    runGame();
}

bool Game::end(Player& player) {
    std::cout << "Congratulations player " << player.getName() << "!!!\n";
    std::cout << "You win!!!\n\n";
    std::cout << "Play again (1 for yes | 0 for no): ";
    int selection;
    std::cin >> selection;
    return selection != 0;
}

bool Game::verifyBoard() {
    //TODO verificar si esta bien
    std::string testing_word;
    for (size_t i = 0; i < 11; i++) {
        for (size_t j = 0; j < 11; j++) {
            if (board[i][j]->value != ' ') {
                if(j != 0 && j != 10) {
                    if (board[i][j - 1]->value == ' ' && board[i][j + 1]->value != ' ')
                        testing_word = parseWord(board[i][j], Direction::RIGHT);
                    else if (board[i][j + 1]->value != ' ') testing_word = parseWord(board[i][j], Direction::RIGHT);
                }
                if(!dictionary[testing_word]) return false;
                if(i != 0 && i != 10) {
                    if (board[i-1][j]->value == ' ' && board[i+1][j]->value != ' ')
                        testing_word = parseWord(board[i][j], Direction::DOWN);
                    else if (board[i+1][j]->value != ' ') testing_word = parseWord(board[i][j], Direction::DOWN);
                }
                if(!dictionary[testing_word]) return false;
            }
        }
    }
    return true;
}

Player* Game::determineTie(std::queue<Player*> players) {
    std::vector<Player*> allPlayers;
    Player *winner = nullptr;

    size_t minimumTiles = 6;

    while(!players.empty()){
        allPlayers.push_back(players.front());
        if (minimumTiles > players.front()->getTiles().size()) {
            minimumTiles = players.front()->getTiles().size();
        }
        players.pop();
    }

    //Elimina jugadores que tienen mas del minimo de caracteres
    for (size_t i = 0; i < allPlayers.size(); i++){
        if (allPlayers.at(i)->getTiles().size() > minimumTiles){
            allPlayers.erase(allPlayers.begin()+i);
        }
    }

    //Verifca puntuacion de caracteres si existe mas de un jugador con la condicion anterior
    if(allPlayers.size() != 1){
        int tempTiles;
        minimumTiles = 'z' * 6;
        for (size_t i = 0; i < allPlayers.size(); i++) {
            tempTiles = 0;
            for (size_t j = 0; j < allPlayers[i]->getTiles().size(); j++) {
                tempTiles += allPlayers[i]->getTiles()[j];
            }
            if (minimumTiles > tempTiles) {
                minimumTiles = tempTiles;
                winner = allPlayers[i];
            }
        }
    } else {
        return allPlayers[0];
    }

    return winner;
}

void Game::runGame() {
    // runs game logic and show functions
    int turnSkiped = 0;
    int option;
    Player* currentPlayer;

    //TODO verificacion de interseccion (por insertar palabra)
    //TODO hacer la verificacion de insertar para ver si la palabra existe en el map

    do{
        currentPlayer = turnOrder.front();
        system("cls");

        // 1) insertar palabra
        // 2) agregar a palabra
        // 3) skip
        std::cout << "What do you want to do player?" << '\n';
        

        switch (condition) {

        }

        if(currentPlayer->getTiles().empty()){
            break;
        }
        turnOrder.pop();
        turnOrder.push(currentPlayer);
    }while(turnSkiped < turnOrder.size());

    if(turnSkiped == turnOrder.size()){
        currentPlayer = determineTie(turnOrder);
    }
    end(*currentPlayer);
}

std::string Game::parseWord(List<char>::listptr nodoActual, Direction direction) {
    std::stringstream ss;
    List<char>::listptr temp = nodoActual;
    while(temp->value != ' '){
        ss << temp->value;
        switch(direction) {
            case Direction::RIGHT:
                temp = temp->right;
                break;
            case Direction::DOWN:
                temp = temp->down;
                break;
        }
    }
    return ss.str();
}

// TODO: this method
int Game::verifyIntersection(const std::string& palabra, int x, int y, Direction direction) {
    /*
     * se maneja desde el insertar si la palabra contiene 2 o mas veces el caracter a insertar y definir en que letra interseca
     * 1) verificar que palabra contenga el caracter en la posicion de x, y
     * 2) verificar rangos de la matriz para la palabra a insertar
     * 3) verificar que haya espacio para la palabra desde la interseccion
     */
    int charReps = 0;
    char charSearched = board[x][y]->value;
    int stringPosition;

    for(auto i: palabra){
        if(i == charSearched)
            charReps++;
    }

    // caracteres a agregar, inicio o final (Modalidad), posicion a insertar inico/final(direccion en matriz), direccion(verificacion cardinal en direccion en matriz)
    if(charReps < 1){
        std::cout << "It seems there is more than 1 of the same character in the word you want to place\n   "
                     "Enter the position of the character you want to intersect with (starting with 0): ";
        std::cin >> stringPosition;

        do {
            if(palabra[stringPosition] == charSearched){
                return
            }
        } while();
    }

    return -1;
}

bool Game::insertWord(std::string palabra, int x, int y, Direction direction,  bool firstTurn) {
    int position;
    if (!firstTurn) {
        position = verifyIntersection(palabra, x, y, direction);
    } else {
        std::cout << "Enter the position of the letter you want to put in the center of the board (starting at 0): ";
        std::cin >> position;
    }
    if (position != -1) {
        for (int i = 0; i < palabra.size(); i++) {
            switch(direction) {
                case Direction::RIGHT:
                    board[x][y - (position - i)]->value = palabra.at(i);
                    break;
                    case Direction::DOWN:
                        board[x - (position - i)][y]->value = palabra.at(i);
                        break;
            }
        }
    }

    return verifyBoard();
}

void Game::eliminateInsertion() {

}

