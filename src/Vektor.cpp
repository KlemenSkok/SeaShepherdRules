
// Vektor.cpp

//? TODO: implement catches for empty list and out of range index


#include "Vektor.hpp"

#include <iostream>



template <typename T>
Vektor<T>::Vektor() {
    start = nullptr;
    konc = nullptr;
}

template <typename T>
Vektor<T>::~Vektor() {
    while(start != nullptr) {
        Node *tmp = start;
        start = start->next;
        if(start != nullptr) {
            start->prev = nullptr;
        }
        delete tmp;
    }
}

template <typename T>
int Vektor<T>::size(){
    int n = 0;
    Node *tmp = start;
    while(tmp != nullptr) {
        n++;
        tmp = tmp->next;
    }
    return n;
}

template <typename T>
void Vektor<T>::push_back(T data) {
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = nullptr;
    tmp->prev = konc;

    if(start == nullptr) {
        start = konc = tmp;
    }
    else {
        konc->next = tmp;
        konc = tmp;
    }
}

template <typename T>
void Vektor<T>::push_front(T data) {
    Node *tmp = new Node;
    tmp->data = data;
    tmp->next = start;
    tmp->prev = nullptr;

    if(start == nullptr) {
        start = konc = tmp;
    }
    else {
        start->prev = tmp;
        start = tmp;
    }
}

template <typename T>
void Vektor<T>::pop_back() {
    if(start == nullptr) {
        std::cout << "[Vektor] Error: cannot pop from empty list\n";
    }
    else if(start == konc) {
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        konc = konc->prev;
        konc->next = nullptr;
        delete tmp;
    }
}

template <typename T>
void Vektor<T>::pop_front() {
    if(start == nullptr) {
        std::cout << "[Vektor] Error: cannot pop from empty list\n";
    }
    else if(start == konc) {
        delete start;
        start = konc = nullptr;
    }
    else {  
        Node *tmp = start;
        start = start->next;
        start->prev = nullptr;
        delete tmp;
    }
}

template <typename T>
void Vektor<T>::erase_at(int index) {
    if(start == nullptr) {
        std::cout << "[Vektor] Error: cannot erase from empty list" << std::endl;
    }
    else if(index < 0 || index >= size()) {
        std::cout << "[Vektor] Error: index out of range" << std::endl;
    }
    else {
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        if(tmp == start) {
            pop_front();
        }
        else if(tmp == konc) {
            pop_back();
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp;
        }
    }
}

template <typename T>
void Vektor<T>::erase_id(int id) {
    //throw std::runtime_error("[Vektor] Error: erase_id not implemented");
    std::cout << "[Vektor] Error: erase_id not implemented for this data type\n";
}


template <typename T>
T& Vektor<T>::operator[](int index) {
    if(start == nullptr) {
        //throw std::out_of_range("[Vektor] Error: cannot access empty list");
        std::cout << "[Vektor] Error: cannot access empty list\n";
    }
    else if(index < 0 || index >= size()) {
        //throw std::out_of_range("[Vektor] Error: index out of range");
        std::cout << "[Vektor] Error: index out of range\n";
    }
    else {
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        return tmp->data;
    }
    return start->data;
}

template <typename T>
T& Vektor<T>::at(int index) {
    if(start == nullptr) {
        //throw std::out_of_range("[Vektor] Error: cannot access empty list");
        std::cout << "[Vektor] Error: cannot access empty list\n";
    }
    else if(index < 0 || index >= size()) {
        //throw std::out_of_range("[Vektor] Error: index out of range");
        std::cout << "[Vektor] Error: index out of range\n";
    }
    else {  
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        return tmp->data;
    }
    return start->data;
}

template <typename T>
void Vektor<T>::clear() {
    while(start != nullptr) {
        Node *tmp = start;
        start = start->next;
        delete tmp;
    }
    konc = nullptr;
}

template <typename T>
T& Vektor<T>::front() {
    if(start == nullptr) {
        //throw std::out_of_range("[Vektor] Error: cannot access empty list");
        std::cout << "[Vektor] Error: cannot access empty list\n";
    }
    return start->data;
}

template <typename T>
T& Vektor<T>::back() {
    if(start == nullptr) {
        //throw std::out_of_range("[Vektor] Error: cannot access empty list");
        std::cout << "[Vektor] Error: cannot access empty list\n";
    }
    return konc->data;
}
