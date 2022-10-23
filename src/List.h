// Autor: El Tigre
// Descripci�n: Definici�n de una lista enlazada simple

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstddef>
#include "Node.h"

// Autor: El Tigre
// Descripci�n: Definici�n de una lista enlazada simple

// Lista que se construye a partir de nodos autoreferenciados
// con datos definidos por el usuario
template<class T> class List {
private:
    // Declaraci�n de cada nodo de la lista: contiene el valor y un apuntador a un nodo
    // Queda oculto para el usuario

    // Apuntador al inicio de la lista
    Node<T>* start;

    void Initialize() { start = nullptr; }

    // Interfaz de la Lista Enlazada Simple
public:

    // Declaraci�n de definici�n de tipos
    typedef Node<T>* listptr;
    typedef const Node<T>* const_listptr;

    // Constructores
    // Default
    List() { Initialize(); }
    // Copia
    explicit List(const List& obj) {
        if (obj.start == nullptr)
            start = nullptr;
        else {
            start = new Node<T>(obj.start->valor);
            listptr current = start;
            listptr currentObj = obj.start->next;
            while (currentObj != nullptr) {
                current->next = new Node<T>(currentObj->valor);
                current = current->next;
                currentObj = currentObj->next;
            }
        }
    }

    // Destructor
    ~List() { EraseList(); }

    // Retorna un apuntador al primer nodo de la lista - modificable
    listptr GetFirstNode() { return start; }

    // Retorna un apuntador al primer nodo de la lista - para un objeto const
    listptr GetFirstNode() const { return start; }

    // Inserta un elemento al final de la lista enlazada
    void Insert(const T& val) {
        listptr newNode;

        try {
            newNode = new Node<T>(val);
        }
        catch (std::bad_alloc exception) {
            return;
        }

        if (start == nullptr)
            start = newNode;
        else {
            listptr tmp = start;
            while (tmp->right != nullptr)
                tmp = tmp->right;
            tmp->next = start;
        }
    }

    // Elimina el nodo especificado de la lista enlazada
    void Eliminate(listptr pointer) {
        // No hay nada que borrar si la lista enlazada est� vac�a
        // o el puntero es NULL
        if (pointer == nullptr || start == nullptr)
            return;

        // Caso #1: El elemento a borrar es el primero de la lista enlazada
        if (start == pointer) {
            start = start->right;
            delete pointer;
        }
            // Caso #2: El elemento se encuentra en alguna otra posici�n de la lista
        else {
            listptr tmp = start;
            listptr tmp2 = tmp->right;
            while (tmp2 != nullptr) {
                if (tmp2 == pointer) {
                    tmp->next = tmp2->right;
                    delete tmp2;
                    return;
                }
                tmp = tmp2;
                tmp2 = tmp2->right;
            }
        }
    }

    // Elimina un nodo de la lista en la posici�n especificada
    void EliminateInPos(std::size_t pos) {
        if (pos <= 0)
            return;

        listptr tmp = start;
        for (std::size_t i = 1; i < pos; ++i) {
            tmp = tmp->right;
            if (tmp == nullptr)
                return;
        }
        Eliminate(tmp);
    }

    // Borra completamente la lista
    void EraseList() {
        listptr tmp;
        while (start != nullptr) {
            tmp = start;
            start = start->right;
            delete tmp;
        }
    }
};

#endif // LIST_H