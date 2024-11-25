#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif


class DLL_EXPORT Packet {
private:
    int packetID;          // Unique ID for the packet
    int size;              // Size of the packet in bytes
    double transmissionTime; // Time taken to transmit the packet (ms)
    int sourceID;          // ID of the user who created the packet
    bool isRetransmitted;  // Flag indicating if the packet is a retransmission
    int priority;          // Packet priority (e.g., high, low)

public:
    // Constructor
    Packet(int size, int sourceID);

    // Getters and Setters
    int getPacketID() const;               // Returns the unique packet ID
    int getSize() const;                   // Returns the packet size
    double getTransmissionTime() const;    // Returns the transmission time
    void setTransmissionTime(double time); // Sets the transmission time
    bool getIsRetransmitted() const;       // Returns the retransmission flag
    void setRetransmitted(bool flag);      // Sets the retransmission flag
    int getPriority() const;               // Returns the packet priority
    void setPriority(int priorityLevel);   // Sets the packet priority
};
