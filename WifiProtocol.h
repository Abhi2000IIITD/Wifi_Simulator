#ifndef WIFIPROTOCOL_H
#define WIFIPROTOCOL_H

#include <iostream>

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

#endif
