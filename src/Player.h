#ifndef SCRABBLE_PLAYER_H
#define SCRABBLE_PLAYER_H

#include <vector>
#include <ostream>

class Player {
private:
    std::string name;
    std::vector<char> tiles;
public:
    Player();

    std::vector<char> &getTiles();

    std::string getName() const;

    void setName(std::string name);

    friend std::ostream &operator<<(std::ostream &os, const Player &player);
    char operator[](int position);
};


#endif //SCRABBLE_PLAYER_H
