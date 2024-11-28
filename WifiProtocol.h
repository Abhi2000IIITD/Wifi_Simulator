#ifndef WIFIPROTOCOL_H
#define WIFIPROTOCOL_H

#include "User.h"            // Fake usage of User.h
#include "Packet.h"          // Fake usage of Packet.h
#include "FrequencyChannel.h" // Fake usage of FrequencyChannel.h
#include "AccessPoint.h"     // Fake usage of AccessPoint.h
#include <random>
#include <iostream>
#include <iomanip>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT WifiProtocol {
public:
    virtual void startSimulation() = 0;
    virtual double calculateThroughput() = 0;
    virtual double calculateLatency() = 0;
    virtual double calculateMaxLatency() = 0;
    virtual ~WifiProtocol() {}
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
    AccessPoint* accessPoint;  
    std::vector<User*> users; 
    FrequencyChannel* frequencyChannel;  

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

    void startSimulation();
    double calculateLatency();
     double calculateThroughput() override;  // Implementation of pure virtual function
    double calculateThroughput(double dataTransmitted, double totalTime);  // Overlo
    double calculateAverageLatency();
    double calculateMaxLatency();
    void resetMetrics();

private:
    int numUsers;                          // Number of users
    double totalDataTransmitted;           // Total data transmitted in bits
    double maxLatency;                     // Maximum latency value
    double totalTime;                      // Total time for the simulation
    std::vector<double> userLatencies;     // Latencies for each user
    double calculateLatencyForRound(int round);
};

#ifndef WIFI7_PROTOCOL_H
#define WIFI7_PROTOCOL_H

#include "WifiProtocol.h"

class DLL_EXPORT Wifi7Protocol : public WifiProtocol {
public:
    Wifi7Protocol(int userCount);
    void startSimulation() override;
    double calculateThroughput() override;
    double calculateLatency() override;
    double calculateMaxLatency() override;

private:
    int userCount;  // Number of users in the simulation
    double totalBandwidth;  // Total bandwidth in Mbps
    double modulationEfficiency;  // Modulation efficiency (example: for 4096-QAM)
    double packetSize;  // Packet size in bits (8 KB in this case)
    
    // Helper functions to calculate throughput and latency
    double calculateRealTimeThroughput(int userCount);
    double calculateRealTimeLatency(int userCount);
    double generatePacket(double lower, double upper);  // Function to generate random variability
};

#endif // WIFI7_PROTOCOL_H


#endif // WIFI7_PROTOCOL_H
