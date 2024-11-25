#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif


#include <queue>
#include "Packet.h"

class DLL_EXPORT User {
private:
    int userID;                         // Unique ID for the user
    std::queue<Packet*> packetQueue;    // Queue of packets to be sent
    double totalLatency;                // Cumulative latency experienced by the user
    int totalPacketsSent;               // Total number of packets sent successfully
    double maxLatency;                  // Maximum latency observed for any packet

public:
    // Constructor
    User(int id);

    // Packet handling
    void addPacket(Packet* packet);     // Adds a packet to the user's queue
    Packet* getNextPacket();            // Retrieves the next packet for transmission

    // Metrics
    void addLatency(double latency);    // Adds latency to the cumulative total
    double calculateAverageLatency() const; // Returns the average latency per packet

    // Getters
    int getUserID() const { return userID; }
    double getTotalLatency() const { return totalLatency; }
    int getPacketsSent() const { return totalPacketsSent; }
    int getPacketsReceived() const { return getPacketsSent(); } // Alias for totalPacketsSent
    double getMaxLatency() const { return maxLatency; }
};
