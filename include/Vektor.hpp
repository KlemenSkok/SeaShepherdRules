
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
    bool empty();

    int size();

    T& operator[](int index);
    T& at(int index);
    T& front();
    T& back();

};


#include "Pirate.hpp"
#include "Whaler.hpp"
#include "Iceberg.hpp"
#include "Atol.hpp"
#include "Utilities.hpp"

// default templates
template class Vektor<int>;
template class Vektor<float>;
template class Vektor<char>;
template class Vektor<std::string>;


// custom templates
template class Vektor<Pirate*>; // enable Pirate* template
template class Vektor<Whaler*>; // enable Whaler* template
template class Vektor<Iceberg*>; // enable Iceberg* template
template class Vektor<Atol*>; // enable Atol* template
template class Vektor<struct ReplayObject>; // enable ReplayObject template