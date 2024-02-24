
// Vektor.hpp

template <typename T>
class Vektor {
    
    Vektor *start;
    Vektor *konc;
    Vektor *next;
    Vektor *prev;
    
    T data;    

public:
    Vektor();
    ~Vektor();

    void push_back(T data);
    void pop_back();
    void push_front(T data);
    void pop_front();

    void erase_at(int index);

    void clear();

    int size();

    T& operator[](int index);
    T& at(int index);

};

template class Vektor<int>;