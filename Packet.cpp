#include "Packet.h"

// Template class definition
template <typename T>
Packet<T>::Packet(int size) : size(size) {
    data = new T[size]; 
}

template <typename T>
Packet<T>::~Packet() {
    delete[] data;  
}

template <typename T>
int Packet<T>::getSize() const {
    return size; 
}

