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
    if (!game.turnOrder.empty()) os << " Turn: " << *game.turnOrder.front() << "\t";
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

bool Game::start(int playerAmount) {
    std::vector<Player*> playerSelectionVector;
    std::string tempName;
    for (int i = 0; i < playerAmount; i++) {
        playerSelectionVector.push_back(new Player());
        std::cout << "Enter your name: ";
        std::cin >> tempName;
        playerSelectionVector.at(i)->setName(tempName);
        for (int j = 0; j < 6; j++) {
            playerSelectionVector.at(i)->getTiles().push_back(letters[rand()%15]);
        }
    }
    for (int i = playerAmount; i > 0; i--) {
        int num = rand()%i;
        turnOrder.push(playerSelectionVector[num]);
        playerSelectionVector.erase(playerSelectionVector.begin() + num);
    }

    bool continueQuestion = runGame();
    return continueQuestion;
}

bool Game::end(Player& player) {
    std::cout << "Congratulations player " << player.getName() << "!!!\n";
    std::cout << "You win!!!\n\n";
    std::cout << "Play again (1 for yes | 0 for no): ";
    while (!turnOrder.empty()) turnOrder.pop();
    int selection;
    std::cin >> selection;
    return selection != 0;
}

bool Game::verifyBoard() {
    std::string testing_word;
    bool right = false, down = false;
    for (size_t i = 0; i < 11; i++) {
        for (size_t j = 0; j < 11; j++) {
            right = false; down = false;
            if (board[i][j]->value != ' ') {
                if(j != 0 && j != 10) {
                    if (board[i][j - 1]->value == ' ' && board[i][j + 1]->value != ' ') {
                        testing_word = parseWord(board[i][j], Direction::RIGHT);
                        right = true;
                    } else if (board[i][j + 1]->value != ' ') {
                        testing_word = parseWord(board[i][j], Direction::RIGHT);
                        right = true;
                    }
                }
                if(!dictionary[testing_word] && right) return false;
                if(i != 0 && i != 10) {
                    if (board[i-1][j]->value == ' ' && board[i+1][j]->value != ' ') {
                        testing_word = parseWord(board[i][j], Direction::DOWN);
                        down = true;
                    } else if (board[i+1][j]->value != ' ')  {
                        testing_word = parseWord(board[i][j], Direction::DOWN);
                        down = true;
                    }
                }
                if(!dictionary[testing_word] && down) return false;
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

// runs game logic and show functions
bool Game::runGame() {
    int option = 0;
    bool firstTurn = true, insertFail;
    int turnSkiped = 0;
    std::string tmpWord;
    int x, y, direction;
    Player* currentPlayer;

    do{
        system("cls");
        Sleep(1000);
        currentPlayer = turnOrder.front();
        std::cin.get();

        std::cout << *this;
        std::cout << "What do you want to do?" << '\n';
        std::cout << " 1) Insert a word" << '\n';
        std::cout << " 2) Extend an existing word" << '\n';
        std::cout << " 3) Skip yout turn" << '\n';
        std::cout << "Select an option: "; std::cin >> option;

        switch (option) {
            case 1:
                if (turnSkiped > 0) turnSkiped = 0;
                std::cout << "What word would you like to enter? ";
                std::cin >> tmpWord;

                //Determina si es el primer turno, creo que no es necesario recibir firstTurn en el metodo insertWord
                if(firstTurn){

                    x = 5;
                    y = 5;
                } else{
                    std::cout << "In what position do you want intersect with a word? " << '\n';
                    std::cout << "ROW: ";
                    std::cin >> x;
                    std::cout << "COLUMN: ";
                    std::cin >> y;
                    std::cout << '\n';
                }

                std::cout << "In what direction do you want the word to be in (0 = Horizontal / 1 = Vertical)? ";
                std::cin >> direction;

                //Inserta el ENUM correcto dependiendo del entero ingresado por usuario
                if(direction == 0){
                    insertFail = insertWord(tmpWord, x, y, Direction::RIGHT, firstTurn);
                } else{
                    insertFail = insertWord(tmpWord, x, y, Direction::DOWN, firstTurn);
                }
                if (firstTurn && insertFail) firstTurn = false;
                break;

                if (firstTurn)  {
                    std::cout << "No words to add to!!!\n";
                    break;
                }
                if (turnSkiped > 0) turnSkiped = 0;
                char somethingFix;
                std::cout << "Would you like to add the beginning or at the end of the word ('b' for beginning | 'e' for end): ";
                std::cin >> somethingFix;
                std::cout << "Enter what you want to add to the word: ";
                std::cin >> tmpWord;

                std::cout << "In what position do you want intersect with a word? " << '\n';
                std::cout << "ROW: ";
                std::cin >> x;
                std::cout << "COLUMN: ";
                std::cin >> y;
                std::cout << '\n';

                std::cout << "In what direction do you want the word to be in (0 = Horizontal / 1 = Vertical)? ";
                std::cin >> direction;

                if(direction == 0){
                    if (somethingFix == 'b') {
                        if (board[x][y-1]->value == ' ') {
                            tmpWord += board[x][y]->value;
                            insertFail = insertWord(tmpWord, x, y, Direction::RIGHT, firstTurn);
                        } else {
                            std::cout << "Invalid Option. Please insert a valid option: ";
                        }
                    } else {
                        if (board[x][y+1]->value == ' ') {
                            tmpWord = board[x][y]->value + tmpWord;
                            insertFail = insertWord(tmpWord, x, y, Direction::RIGHT, firstTurn);
                        } else {
                            std::cout << "Invalid Option. Please insert a valid option: ";
                        }
                    }
                } else {
                    if (somethingFix == 'b') {
                        if (board[x-1][y]->value == ' ') {
                            tmpWord += board[x][y]->value;
                            insertFail = insertWord(tmpWord, x, y, Direction::DOWN, firstTurn);
                        } else {
                            std::cout << "Invalid Option. Please insert a valid option: ";
                        }
                    } else {
                        if (board[x+1][y]->value == ' ') {
                            tmpWord = board[x][y]->value + tmpWord;
                            insertFail = insertWord(tmpWord, x, y, Direction::DOWN, firstTurn);
                        } else {
                            std::cout << "Invalid Option. Please insert a valid option: ";
                        }
                    }
                }
                break;

            case 3:
                turnSkiped++;
                std::cout << "Skipped!" << '\n';
                Sleep(500);
                insertFail = true;
                break;

            default:
                std::cin.ignore();
                std::cout << "Invalid Option. Please insert a valid option: ";
                Sleep(500);
                break;
        }

        if(currentPlayer->getTiles().empty()){
            break;
        }
        if (insertFail) {
            turnOrder.pop();
            turnOrder.push(currentPlayer);
        } else {
            std::cout << "Error inserting try again!\n";
            Sleep(1000);
        }
    }while(turnSkiped < turnOrder.size());

    if(turnSkiped == turnOrder.size()){
        currentPlayer = determineTie(turnOrder);
    }
    bool continueQuestion = end(*currentPlayer);
    return continueQuestion;
}

std::string Game::parseWord(List<char>::listptr nodoActual, Direction direction) {
    std::stringstream ss;
    List<char>::listptr temp = nodoActual;
    while(temp){
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

int Game::verifyIntersection(const std::string& palabra, int x, int y) {
    /*
     * se maneja desde el insertar si la palabra contiene 2 o mas veces el caracter a insertar y definir en que letra interseca
     * 1) verificar que palabra contenga el caracter en la posicion de x, y
     * 2) verificar rangos de la matriz para la palabra a insertar
     * 3) verificar que haya espacio para la palabra desde la interseccion
     */
    int charReps = 0;
    char charSearched = board[x][y]->value;
    int stringPosition;

    //cuenta repeticiones
    for(auto i: palabra){
        if(i == charSearched)
            charReps++;
    }

    // verifica si hay mas que una repeticion
    if(charReps > 1){
        std::cout << "It seems there is more than 1 of the same character in the word you want to place\n";

        //verifica el valor de entrada para que sea una letra igual al caracter buscado
        do {
            std::cout <<"Enter the position of the character you want to intersect with (starting from 0): ";
            std::cin >> stringPosition;
            if(stringPosition == -1){
                break;
            }
            else if(palabra[stringPosition] == charSearched){
                return stringPosition;
            }
            else if(stringPosition > palabra.size() ||stringPosition < 0 || palabra[stringPosition] != charSearched){
                std::cout << "The given value is either out of range or not the same as the character given before.";
            }
        } while(true);
    }
    else{
        std::cout <<"Enter the position of the character you want to intersect with (starting from 0): ";
        std::cin >> stringPosition;
        return stringPosition;
    }

    return -1;
}

bool Game::insertWord(std::string palabra, int x, int y, Direction direction,  bool firstTurn) {
    int position;
    if (!firstTurn) {
        position = verifyIntersection(palabra, x, y);
    } else {
        std::cout << "Enter the position of the letter you want to put in the center of the board (starting at 0): ";
        std::cin >> position;
    }

    switch(direction) {
        case Direction::RIGHT:
            for (int i = 1; i < position; i++) {
                if (y - i < 0) {
                   return false;
                } else {
                    if (board[x][y-i]->value != ' ') return false;
                }
            }
            for (int i = position +1; i < palabra.size(); i++) {
                if (y + i > 10) {
                    return false;
                } else {
                    if (board[x][y-i]->value != ' ') return false;
                }
            }
            break;
        case Direction::DOWN:
            for (int i = 1; i < position; i++) {
                if (x - i < 0) {
                    return false;
                } else {
                    if (board[x-i][y]->value != ' ') return false;
                }
            }
            for (int i = position +1; i < palabra.size(); i++) {
                if (x + i > 10) {
                    return false;
                } else {
                    if (board[x-i][y]->value != ' ') return false;
                }
            }
            break;
    }

    if (position != -1) {
        for (int i = 0; i < palabra.size(); i++) {
            switch(direction) {
                case Direction::RIGHT:
                    board[x][y - (position - i)]->value = palabra.at(i);
                    if (board[x-1][y - (position - i)]->value != ' ') board[x-1][y - (position - i)]->down = board[x][y -(position - i)];
                    if (board[x+1][y - (position - i)]->value != ' ') board[x][y - (position - i)]->down = board[x+1][y - (position - i)];
                    if (board[x][y - (position - i) - 1]->value != ' ') board[x][y - (position - i)-1]->right = board[x][y - (position -i)];
                    if (board[x][y - (position - i) + 1]->value != ' ') board[x][y - (position - i)]->right = board[x][y - (position - i) + 1];
                    break;
                case Direction::DOWN:
                    board[x - (position - i)][y]->value = palabra.at(i);
                    if (board[x-1][y - (position - i)]->value != ' ') board[x-1][y - (position - i)]->down = board[x][y -(position - i)];
                    if (board[x+1][y - (position - i)]->value != ' ') board[x][y - (position - i)]->down = board[x+1][y - (position - i)];
                    if (board[x][y - (position - i) - 1]->value != ' ') board[x][y - (position - i)-1]->right = board[x][y - (position -i)];
                    if (board[x][y - (position - i) + 1]->value != ' ') board[x][y - (position - i)]->right = board[x][y - (position - i) + 1];
                    break;
            }
        }
    } else return false;
    bool verifiedBoard = verifyBoard();
    if (!verifiedBoard) {
        for (int i = 0; i < palabra.size(); i++) {
            if (i != position) {
                switch (direction) {
                    case Direction::RIGHT: {
                        board[x][y - (position - i)]->value = ' ';
                        if (board[x - 1][y - (position - i)]->value != ' ')
                            board[x - 1][y - (position - i)]->down = nullptr;
                        if (board[x + 1][y - (position - i)]->value != ' ')
                            board[x][y - (position - i)]->down = nullptr;
                        if (board[x][y - (position - i) - 1]->value != ' ')
                            board[x][y - (position - i) - 1]->right = nullptr;
                        if (board[x][y - (position - i) + 1]->value != ' ')
                            board[x][y - (position - i)]->right = nullptr;
                        break;
                    }
                    case Direction::DOWN:
                        board[x - (position - i)][y]->value = ' ';
                        if (board[x - 1][y - (position - i)]->value != ' ')
                            board[x - 1][y - (position - i)]->down = nullptr;
                        if (board[x + 1][y - (position - i)]->value != ' ')
                            board[x][y - (position - i)]->down = nullptr;
                        if (board[x][y - (position - i) - 1]->value != ' ')
                            board[x][y - (position - i) - 1]->right = nullptr;
                        if (board[x][y - (position - i) + 1]->value != ' ')
                            board[x][y - (position - i)]->right = nullptr;
                        break;
                }
            }
        }
        return false;
    } else {
        for (int i = 0; i < turnOrder.front()->getTiles().size(); i++) {
            for (int j = 0; j < palabra.size(); j++) {
                if (turnOrder.front()->getTiles()[i] == palabra.at(j)) {
                    turnOrder.front()->getTiles().erase(turnOrder.front()->getTiles().begin() + i);
                }
            }
        }
    }
    return true;
}