#include "WifiProtocol.h"
#include <iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>

using namespace std;

Wifi4Protocol::Wifi4Protocol(int userCount, int maxBackoffTime)
    : userCount(userCount), maxBackoffTime(maxBackoffTime) {}

void Wifi4Protocol::startSimulation() {
    // Simulate WiFi 4 communication
    cout << "Starting WiFi 4 simulation with " << userCount << " users.\n";

    // Simulate users attempting to transmit
    for (int i = 0; i < userCount; ++i) {
        double backoffTime = rand() % maxBackoffTime; // Generate random backoff time
        totalBackoffTime += backoffTime;             // Accumulate total backoff time
        totalPacketsTransmitted++;                  // Count packets transmitted
    }

    // Display metrics
    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double Wifi4Protocol::calculateThroughput() {
    double bandwidth = 20.0;                // MHz
    double modulationEfficiency = 6.0;     // Bits per symbol for 256-QAM with 5/6 coding rate
    double packetSize = 8192.0;             // 1 KB packet size in bits
    double transmissionTime = 60.0 / 1000; // 60 ms in seconds

    // Adjust throughput based on user count
    double throughputPerUser = (packetSize / transmissionTime) * modulationEfficiency;
    double totalThroughput = (bandwidth / userCount) * throughputPerUser; // Divide bandwidth among users

    return totalThroughput / 1e6; // Convert bits per second to Mbps
}

double Wifi4Protocol::calculateLatency() {
    // Average backoff time is proportional to the number of users
    double avgBackoffTime = (maxBackoffTime / 2.0) * (1 + (userCount / 10.0)); // Simulate contention
    double transmissionTime = 60.0; // ms
    return avgBackoffTime + transmissionTime;
}

double Wifi4Protocol::calculateMaxLatency() {
    // Dynamically adjust maxBackoffTime based on user count
    double dynamicMaxBackoff = maxBackoffTime * (1 + (userCount / 10.0)); // Increase with users
    return dynamicMaxBackoff + 60.0; // Add transmission time
}
