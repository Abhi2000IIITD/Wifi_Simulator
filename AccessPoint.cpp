#include "AccessPoint.h"
#include <algorithm>
#include <iostream>

// Constructor
AccessPoint::AccessPoint(int id, FrequencyChannel* channel)
    : apID(id), channel(channel), totalPacketsTransmitted(0), totalTime(0.0) {}

// Add a user to the AP
void AccessPoint::connectUser(User* user) {
    connectedUsers.push_back(user);
    std::cout << "User " << user->getUserID() << " connected to Access Point " << apID << std::endl;
}

// Remove a user from the AP
void AccessPoint::disconnectUser(int userID) {
    auto it = std::remove_if(connectedUsers.begin(), connectedUsers.end(),
                             [userID](User* user) { return user->getUserID() == userID; });
    if (it != connectedUsers.end()) {
        connectedUsers.erase(it, connectedUsers.end());
        std::cout << "User " << userID << " disconnected from Access Point " << apID << std::endl;
    }
}

// Handles packet transmission to a specific user
void AccessPoint::transmitPacket(Packet* packet, User* user) {
    if (channel->checkIfFree()) {
        // Simulate successful transmission
        double transmissionTime = static_cast<double>(packet->getSize() * 8) / channel->getBandwidth(); // Size in bits / bandwidth in Mbps
        totalTime += transmissionTime;
        totalPacketsTransmitted++;

        user->addLatency(transmissionTime); // Update user latency
        std::cout << "Packet with ID " << packet->getPacketID() << " transmitted to User "
                  << user->getUserID() << " via Access Point " << apID << std::endl;

    } else {
        // Add to transmission queue if the channel is busy
        transmissionQueue.push(packet);
        std::cout << "Channel busy! Packet with ID " << packet->getPacketID() << " added to transmission queue." << std::endl;
    }
}

// Handles packet collisions
void AccessPoint::handlePacketCollision(Packet* packet) {
    std::cout << "Collision detected for packet ID " << packet->getPacketID()
              << ". Retrying..." << std::endl;
    transmissionQueue.push(packet); // Retry by adding to queue
}

// Calculate throughput (Mbps)
double AccessPoint::calculateThroughput() const {
    if (totalTime == 0) {
        return 0.0;
    }
    return (totalPacketsTransmitted * 8.0) / totalTime; // Convert bytes to bits, then divide by total time in seconds
}

// Calculate average latency
double AccessPoint::calculateAverageLatency() const {
    double totalLatency = 0.0;
    int totalPackets = 0;

    for (const auto& user : connectedUsers) {
        totalLatency += user->getTotalLatency();
        totalPackets += user->getPacketsReceived();
    }

    return totalPackets > 0 ? totalLatency / totalPackets : 0.0;
}

// Calculate maximum latency
double AccessPoint::calculateMaxLatency() const {
    double maxLatency = 0.0;

    for (const auto& user : connectedUsers) {
        maxLatency = std::max(maxLatency, user->getMaxLatency());
    }

    return maxLatency;
}
