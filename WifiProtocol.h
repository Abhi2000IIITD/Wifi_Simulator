#ifndef WIFIPROTOCOL_H
#define WIFIPROTOCOL_H

#include <iostream>
#include <vector>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif
class User;  // Forward declaration to avoid circular dependency

class DLL_EXPORT WifiProtocol {
public:
    virtual void startSimulation() = 0;
    virtual double calculateThroughput() = 0;
    virtual double calculateLatency() = 0;
    virtual double calculateMaxLatency() = 0;
    virtual ~WifiProtocol() {}
protected:
    int userCount;
    int subChannelCount;
    std::vector<User*> users;  // List of users in simulation
    double totalDataTransmitted;
    double totalTime;
    double maxLatency;
    int currentUserIndex;
    std::vector<int> subChannelSizes;
};

// WiFi 4 Protocol Simulation
class DLL_EXPORT Wifi4Protocol : public WifiProtocol {
public:
    Wifi4Protocol(int userCount, int maxBackoffTime = 30);
    void startSimulation() override;
    double calculateThroughput() override;
    double calculateLatency() override;
    double calculateMaxLatency() override;

private:
    int userCount;
    int maxBackoffTime;
    double totalBackoffTime;
    double maxBackoffTimeRecorded;
    int totalPacketsTransmitted;

    void resetMetrics();
};

// WiFi 5 Protocol Simulation
class DLL_EXPORT Wifi5Protocol : public WifiProtocol {
public:
    Wifi5Protocol(int userCount);
    void startSimulation() override;
    double calculateThroughput() override;
    double calculateLatency() override;
    double calculateMaxLatency() override;

private:
    int userCount;
    double totalTime;           // Total simulation time
    double totalDataTransmitted; // Total data transmitted in Mbps
    int totalRounds;            // Total rounds completed
    double maxLatency;

    void resetMetrics();
};
class DLL_EXPORT Wifi6Protocol : public WifiProtocol {
public:
    Wifi6Protocol(int userCount);
    void startSimulation() override;
    double calculateThroughput() override;
    double calculateLatency() override;
    double calculateMaxLatency() override;

private:
    int userCount;
    int subChannelCount;           // Total 2 MHz sub-channels (10 sub-channels)
    std::vector<User*> users;      // List of users in simulation
    std::vector<int> subChannelSizes;  // Array of sub-channel sizes (each 2 MHz)
    int currentUserIndex;          // Round-robin index for assigning users to channels
    double totalDataTransmitted;   // Total data transmitted in Mbps
    double totalTime;              // Total simulation time
    double maxLatency;  
    double throughput;           // Maximum latency observed during simulation

    void resetMetrics();
    void allocateSubChannels();
};


#endif