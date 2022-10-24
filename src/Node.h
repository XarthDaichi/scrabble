#ifndef SCRABBLE_NODE_H
#define SCRABBLE_NODE_H

template<class T> struct Node {
    T value;
    Node* right;
    Node* down;
    // Constructor del Node - asigna NULL si se invoca sin el segundo par�metro
    Node(T val, Node* right = nullptr, Node* down = nullptr) : value{ val }, right{ right }, down{ down } {}
};

#endif //SCRABBLE_NODE_H
