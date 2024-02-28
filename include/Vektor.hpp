
// Vektor.hpp

#pragma once

#include "Logger.hpp"

template <typename T>
class Vektor {
    
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };

    Node *start, *konc;

public:
    Vektor();
    ~Vektor();

    void push_back(T data);
    void pop_back();
    void push_front(T data);
    void pop_front();

    void erase_at(int index);
    void erase_id(int id);	

    void clear();

    int size();

    T& operator[](int index);
    T& at(int index);
    T& front();
    T& back();

};


#include "Enemy.hpp"
#include "Whaler.hpp"

template class Vektor<int>; // enable int template
template class Vektor<Enemy*>; // enable Enemy* template
template class Vektor<Whaler*>; // enable Whaler* template