#include "User.h"
#include <iostream>

// Constructor
User::User(int id) : userID(id), totalLatency(0.0), totalPacketsSent(0), maxLatency(0.0) {}

// Adds a packet to the user's queue
void User::addPacket(Packet* packet) {
    packetQueue.push(packet);
    std::cout << "Packet with ID " << packet->getPacketID() << " added to User " << userID << "'s queue." << std::endl;
}

// Retrieves the next packet for transmission
Packet* User::getNextPacket() {
    if (packetQueue.empty()) {
        std::cout << "No packets in User " << userID << "'s queue." << std::endl;
        return nullptr;
    }

    Packet* nextPacket = packetQueue.front();
    packetQueue.pop();
    return nextPacket;
}

// Adds latency to the user's cumulative total
void User::addLatency(double latency) {
    totalLatency += latency;
    totalPacketsSent++;
    if (latency > maxLatency) {
        maxLatency = latency;
    }
    std::cout << "Latency " << latency << " ms added for User " << userID << ". Total latency now: " << totalLatency << std::endl;
}

// Calculates the average latency per packet
double User::calculateAverageLatency() const {
    return totalPacketsSent > 0 ? totalLatency / totalPacketsSent : 0.0;
}
