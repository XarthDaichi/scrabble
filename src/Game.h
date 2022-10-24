//
// Created by Xarthy on 0019 October 19, 2022.
//

#ifndef SCRABBLE_GAME_H
#define SCRABBLE_GAME_H
#include "List.h"
#include "Player.h"
#include "enum.h"
#include <vector>
#include <queue>
// Para verificar algunas cosas de los mapas usamos: https://www.geeksforgeeks.org/map-associative-containers-the-c-standard-template-library-stl/
#include <map>
#include <ostream>
#include <fstream>
#include <string>
#include <sstream>

// Consulted https://cplusplus.com/reference/cstdlib/rand/ for random
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class Game {
private:
    List<char>::listptr board[11][11]; // Node * board[10][10]
    std::map<std::string, bool> dictionary;
    std::queue<Player*> turnOrder;

    //TODO verificar si necesitamos los vectores siguientes al final
//    std::vector<List<char>::listptr> rightWords;
//    std::vector<List<char>::listptr> downWords;

public:
    //TODO metodo ingresar palabra con verificacion primer turno, direccion, si se pone paralela a otra palabra que esta tambien exista en el diccionario, conectar nodos
    //TODO cambiar palabra

    Game();

    const std::map<std::string, bool> &getDictionary() const;

    void setDictionary(const std::map<std::string, bool> &dictionary);

    const std::queue<Player*> &getTurnOrder() const;

    void setTurnOrder(const std::queue<Player*> &turnOrder);

    friend std::ostream &operator<<(std::ostream &os, const Game &game);

    void parseDictionary(std::string fileName);

    std::string parseWord(List<char>::listptr, Direction direction);

    void start(int playerAmount);

    bool end(Player& player);

    bool verifyBoard();

    //TODO verifica existencia de la palabra en el map
    //TODO if primer turno no verificar interseccion
    bool insertWord(std::string palabra, int x, int y, Direction direction,  bool firstTurn);

    void eliminateInsertion();

    //TODO verifica existencia del caracter en posicion y si la direccion escogida no tiene ningun problema
    int verifyIntersection(const std::string& palabra, int x, int y, Direction direction);

    Player* determineTie(std::queue<Player*> players);

    void runGame();
};


#endif //SCRABBLE_GAME_H
