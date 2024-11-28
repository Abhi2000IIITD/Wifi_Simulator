#include "Packet.h"

Packet::Packet(int size) : size(size) {}

Packet::~Packet() {}

int Packet::getSize() const {
    return size;  // Return the size of the packet
}
