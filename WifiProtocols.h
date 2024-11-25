#pragma once

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif


#include "AccessPoint.h"
#include "User.h"
#include <vector>

// Abstract Base Class
class DLL_EXPORT WiFiProtocol {
public:
    virtual ~WiFiProtocol() {}

    // Pure virtual methods
    virtual void simulate() = 0;         // Simulates the protocol
    virtual void calculateMetrics() = 0; // Calculates throughput, latency, etc.
};

// WiFi4 Protocol: Simulates CSMA/CA
class DLL_EXPORT WiFi4 : public WiFiProtocol {
private:
    AccessPoint* ap;
    double backoffTime; // Time spent in backoff (ms)

public:
    WiFi4(AccessPoint* ap);
    void simulate() override;
    void calculateMetrics() override;
};

// WiFi5 Protocol: Simulates MU-MIMO
class DLL_EXPORT WiFi5 : public WiFiProtocol {
private:
    AccessPoint* ap;
    std::vector<User*> users;

public:
    WiFi5(AccessPoint* ap, const std::vector<User*>& users);
    void simulate() override;
    void calculateMetrics() override;
};

// WiFi6 Protocol: Simulates OFDMA
class DLL_EXPORT WiFi6 : public WiFiProtocol {
private:
    AccessPoint* ap;
    std::vector<int> subChannelAllocations; // Sub-channel allocations

public:
    WiFi6(AccessPoint* ap, const std::vector<int>& subChannelAllocations);
    void simulate() override;
    void calculateMetrics() override;
};
