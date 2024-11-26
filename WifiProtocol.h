#ifndef WIFIPROTOCOL_H
#define WIFIPROTOCOL_H

#include <vector>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT WifiProtocol {
public:
    virtual void startSimulation() = 0;        // Start simulation for the protocol
    virtual double calculateThroughput() = 0; // Calculate throughput
    virtual double calculateLatency() = 0;    // Calculate average latency
    virtual double calculateMaxLatency() = 0; // Calculate maximum latency
    virtual ~WifiProtocol() {}                // Virtual destructor for cleanup
};

// WiFi 4-specific implementation of WifiProtocol
class DLL_EXPORT Wifi4Protocol : public WifiProtocol {
public:
    Wifi4Protocol(int userCount, int maxBackoffTime = 30);

    void startSimulation() override;
    double calculateThroughput() override;
    double calculateLatency() override;
    double calculateMaxLatency() override;

private:
    int userCount;         // Number of users
    int maxBackoffTime;    // Maximum backoff time in milliseconds
    double totalBackoffTime = 0.0;   // Total accumulated backoff time
    int totalPacketsTransmitted = 0; // Total packets transmitted
};

#endif
