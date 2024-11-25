#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

#include <vector>
#include <queue>
#include "User.h"
#include "FrequencyChannel.h"
#include "Packet.h"

class DLL_EXPORT AccessPoint {
private:
    int apID; // Unique ID for the access point
    std::vector<User*> connectedUsers; // List of connected users
    FrequencyChannel* channel; // Associated frequency channel
    int totalPacketsTransmitted; // Total packets transmitted
    double totalTime; // Total transmission time
    std::queue<Packet*> transmissionQueue; // Queue of packets awaiting transmission

public:
    // Constructor
    AccessPoint(int id, FrequencyChannel* channel);

    // User management
    void connectUser(User* user);
    void disconnectUser(int userID);

    // Transmission
    void transmitPacket(Packet* packet, User* user);
    void handlePacketCollision(Packet* packet);

    // Metrics calculation
    double calculateThroughput() const;
    double calculateAverageLatency() const;
    double calculateMaxLatency() const;

    // Utility
    int getAPID() const { return apID; }
    std::vector<User*>& getConnectedUsers() { return connectedUsers; }
    FrequencyChannel* getChannel() const { return channel; }
};
