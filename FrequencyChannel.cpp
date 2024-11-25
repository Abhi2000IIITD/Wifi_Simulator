#include "FrequencyChannel.h"
#include <iostream>

// Constructor
FrequencyChannel::FrequencyChannel(double bandwidth)
    : isFree(true), bandwidth(bandwidth) {}

// Returns true if the channel is free
bool FrequencyChannel::checkIfFree() const {
    return isFree;
}

// Sets the channel status to busy
void FrequencyChannel::occupyChannel() {
    isFree = false;
    std::cout << "Channel is now busy." << std::endl;
}

// Sets the channel status to free
void FrequencyChannel::releaseChannel() {
    isFree = true;
    std::cout << "Channel is now free." << std::endl;
}

// Adds a packet to the queue
void FrequencyChannel::addPacketToQueue(Packet* packet) {
    transmissionQueue.push(packet);
    std::cout << "Packet with ID " << packet->getPacketID() << " added to the channel queue." << std::endl;
}

// Retrieves the next packet for transmission
Packet* FrequencyChannel::getNextPacketFromQueue() {
    if (transmissionQueue.empty()) {
        std::cout << "No packets in the transmission queue." << std::endl;
        return nullptr;
    }

    Packet* nextPacket = transmissionQueue.front();
    transmissionQueue.pop();
    return nextPacket;
}

// Returns the channel bandwidth
double FrequencyChannel::getBandwidth() const {
    return bandwidth;
}
