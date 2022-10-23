//
// Created by Xarthy on 0022 October 22, 2022.
//

#ifndef SCRABBLE_NODE_H
#define SCRABBLE_NODE_H

template<class T> struct Node {
    T value;
    Node* right;
    Node* below;
    // Constructor del Node - asigna NULL si se invoca sin el segundo par�metro
    Node(T val, Node* right = nullptr, Node* below = nullptr) : value{ val }, right{ right }, below{ below } {}
};

#endif //SCRABBLE_NODE_H
