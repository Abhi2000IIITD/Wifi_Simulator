#include "Packet.h"

// Constructor
Packet::Packet(int size, int sourceID)
    : packetID(sourceID), size(size), transmissionTime(0.0), sourceID(sourceID), isRetransmitted(false), priority(0) {}

// Returns the unique packet ID
int Packet::getPacketID() const {
    return packetID;
}

// Returns the packet size
int Packet::getSize() const {
    return size;
}

// Returns the transmission time
double Packet::getTransmissionTime() const {
    return transmissionTime;
}

// Sets the transmission time
void Packet::setTransmissionTime(double time) {
    transmissionTime = time;
}

// Returns the retransmission flag
bool Packet::getIsRetransmitted() const {
    return isRetransmitted;
}

// Sets the retransmission flag
void Packet::setRetransmitted(bool flag) {
    isRetransmitted = flag;
}

// Returns the packet priority
int Packet::getPriority() const {
    return priority;
}

// Sets the packet priority
void Packet::setPriority(int priorityLevel) {
    priority = priorityLevel;
}
