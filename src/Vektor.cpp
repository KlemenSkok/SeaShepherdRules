
// Vektor.cpp

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
        Vektor<T> *tmp = start;
        start = start->next;
        delete tmp;
    }
}

template <typename T>
int Vektor<T>::size(){
    int n = 0;
    Vektor<T> *tmp = start;
    while(tmp != nullptr) {
        n++;
        tmp = tmp->next;
    }
    return n;
}

template <typename T>
void Vektor<T>::push_back(T data) {
    Vektor<T> *tmp = new Vektor<T>;
    tmp->data = data;

    if(start == nullptr) {
        start = tmp;
        konc = tmp;
    }
    else {
        konc->next = tmp;
        tmp->prev = konc;
        konc = tmp;
    }
}

template <typename T>
void Vektor<T>::push_front(T data) {
    Vektor<T> *tmp = new Vektor<T>;
    tmp->data = data;

    if(start == nullptr) {
        start = konc = tmp;
    }
    else {
        start->prev = tmp;
        tmp->next = start;
        start = tmp;
    }
}

template <typename T>
void Vektor<T>::pop_back() {
    if(start == nullptr) {

    }
    else if(start == konc) {
        delete start;
        start = konc = nullptr;
    }
    else {
        Vektor<T> *tmp = konc;
        konc = konc->prev;
        konc->next = nullptr;
        delete tmp;
    }
}

template <typename T>
void Vektor<T>::pop_front() {
    if(start == nullptr) {

    }
    else if(start == konc) {
        delete start;
        start = konc = nullptr;
    }
    else {
        Vektor<T> *tmp = start;
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
        Vektor<T> *tmp = start;
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
T& Vektor<T>::operator[](int index) {
    if(start == nullptr) {
        throw std::out_of_range("[Vektor] Error: cannot access empty list");
    }
    else if(index < 0 || index >= size()) {
        throw std::out_of_range("[Vektor] Error: index out of range");
    }
    else {
        Vektor<T> *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        return tmp->data;
    }
}

template <typename T>
T& Vektor<T>::at(int index) {
    if(start == nullptr) {
        throw std::out_of_range("[Vektor] Error: cannot access empty list");
    }
    else if(index < 0 || index >= size()) {
        throw std::out_of_range("[Vektor] Error: index out of range");
    }
    else {
        Vektor<T> *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        return tmp->data;
    } 
}

template <typename T>
void Vektor<T>::clear() {
    while(start != nullptr) {
        Vektor<T> *tmp = start;
        start = start->next;
        delete tmp;
    }
    konc = nullptr;
}

