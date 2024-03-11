
// Vektor.cpp

#include "Vektor.hpp"



//-------------------------------------------------//
//                 Default templates               //
//-------------------------------------------------//


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
        Logger::Warning("@ Vektor - cannot erase from empty list");
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
        Logger::Warning("@ Vektor - cannot erase from empty list");    }
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
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
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
    Logger::Warning("@ Vektor - erase_id not implemented for this data type");
}


template <typename T>
T& Vektor<T>::operator[](int index) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot access empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
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
        Logger::Warning("@ Vektor - cannot access empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
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
bool Vektor<T>::empty() {
    if(this->start == nullptr) 
        return true;
    return false;
}


template <typename T>
T& Vektor<T>::front() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot access empty list");
    }
    return start->data;
}

template <typename T>
T& Vektor<T>::back() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot access empty list");
    }
    return konc->data;
}






//-------------------------------------------------//
//              overloads for Whaler               //
//-------------------------------------------------//


#include "Whaler.hpp"

template <>
void Vektor<Whaler*>::erase_id(int id) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else {
        Node *tmp = start;
        while(tmp != nullptr && tmp->data->object_ID != id) {
            tmp = tmp->next;
        }
        if(tmp == nullptr) {
            Logger::Error("@ Vektor - id not found");
        }
        else if(tmp == start) { // first element
            if(start == konc) { //only element
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else { // just first
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) { // last element
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}

template <>
void Vektor<Whaler*>::clear() {
    while(start != nullptr) {
        Node *tmp = start;
        start = start->next;
        delete tmp->data;
        delete tmp;
    }
    start = konc = nullptr;
}

template<>
Vektor<Whaler*>::~Vektor() {
    clear();
}

template <>
void Vektor<Whaler*>::pop_back() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        konc = konc->prev;
        konc->next = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Whaler*>::pop_front() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        start = start->next;
        start->prev = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Whaler*>::erase_at(int index) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
    }
    else {
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        if(tmp == start) {
            if(start == konc) {
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else {
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) {
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}


//---------------------------------------------------//
//               overloads for Iceberg               //
//---------------------------------------------------//

#include "Iceberg.hpp"

template <>
void Vektor<Iceberg*>::erase_id(int id) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else {
        Node *tmp = start;
        while(tmp != nullptr && tmp->data->object_ID != id) {
            tmp = tmp->next;
        }
        if(tmp == nullptr) {
            Logger::Error("@ Vektor - id not found");
        }
        else if(tmp == start) { // first element
            if(start == konc) { //only element
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else { // just first
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) { // last element
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}

template <>
void Vektor<Iceberg*>::clear() {
    while(start != nullptr) {
        Node *tmp = start;
        start = start->next;
        delete tmp->data;
        delete tmp;
    }
    start = konc = nullptr;
}

template<>
Vektor<Iceberg*>::~Vektor() {
    clear();
}

template <>
void Vektor<Iceberg*>::pop_back() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        konc = konc->prev;
        konc->next = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Iceberg*>::pop_front() {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(start == konc) {
        delete start->data;
        delete start;
        start = konc = nullptr;
    }
    else {
        Node *tmp = konc;
        start = start->next;
        start->prev = nullptr;
        delete tmp->data;
        delete tmp;
    }
}

template <>
void Vektor<Iceberg*>::erase_at(int index) {
    if(start == nullptr) {
        Logger::Warning("@ Vektor - cannot erase from empty list");
    }
    else if(index < 0 || index >= size()) {
        Logger::Error("@ Vektor - index out of range");
    }
    else {
        Node *tmp = start;
        while(index > 0) {
            tmp = tmp->next;
            index--;
        }
        if(tmp == start) {
            if(start == konc) {
                start = konc = nullptr;
                delete tmp->data;
                delete tmp;
            }
            else {
                start = start->next;
                start->prev = nullptr;
                delete tmp->data;
                delete tmp;
            }
        }
        else if(tmp == konc) {
            konc = konc->prev;
            konc->next = nullptr;
            delete tmp->data;
            delete tmp;
        }
        else {
            tmp->prev->next = tmp->next;
            tmp->next->prev = tmp->prev;
            delete tmp->data;
            delete tmp;
        }
    }
}