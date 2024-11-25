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

class DLL_EXPORT FrequencyChannel {
private:
    bool isFree;                          // Indicates whether the channel is free or busy
    double bandwidth;                     // Total bandwidth of the channel (e.g., 20 MHz)
    std::queue<Packet*> transmissionQueue; // Queue of packets awaiting transmission

public:
    // Constructor
    FrequencyChannel(double bandwidth);

    // Channel Status
    bool checkIfFree() const;             // Returns true if the channel is free
    void occupyChannel();                 // Sets the channel status to busy
    void releaseChannel();                // Sets the channel status to free

    // Queue Handling
    void addPacketToQueue(Packet* packet); // Adds a packet to the queue
    Packet* getNextPacketFromQueue();      // Retrieves the next packet for transmission

    // Getter for bandwidth
    double getBandwidth() const;          // Returns the channel bandwidth in Mbps
};
