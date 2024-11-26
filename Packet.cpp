#include "Packet.h"

Packet::Packet(int size) : size(size) {}

Packet::~Packet() {}

int Packet::getSize() const {
    return size;
}
