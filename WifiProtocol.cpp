#include "WifiProtocol.h"
#include <iostream>
#include <random>
#include <algorithm>

using namespace std;

Wifi4Protocol::Wifi4Protocol(int userCount, int maxBackoffTime)
    : userCount(userCount), maxBackoffTime(maxBackoffTime) {
    resetMetrics();
}

void Wifi4Protocol::startSimulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxBackoffTime);

    cout << "Starting WiFi 4 simulation with " << userCount << " users.\n";

    for (int i = 0; i < userCount; ++i) {
        double backoffTime = dist(gen);
        totalBackoffTime += backoffTime;
        totalPacketsTransmitted++;
        maxBackoffTimeRecorded = max(maxBackoffTimeRecorded, backoffTime);
        //cout << "User " << i + 1 << " backoff time: " << backoffTime << " ms\n";
    }

    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double Wifi4Protocol::calculateThroughput() {
    double bandwidth = 20.0;                // MHz
    double modulationEfficiency = 6.0;     // Bits per symbol for 256-QAM with 5/6 coding rate
    double packetSize = 8192.0;             // 1 KB packet size in bits
    double transmissionTime = 60.0 / 1000; // 60 ms in seconds

    // Random factor to simulate real-world variability
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> randomFactor(0.8, 1.0); // Random factor between 0.8 and 1.0

    double throughputPerUser = (packetSize / transmissionTime) * modulationEfficiency;
    double randomBandwidth = bandwidth * randomFactor(gen);  // Randomized bandwidth
    double totalThroughput = (randomBandwidth / userCount) * throughputPerUser; // Adjust throughput

    return totalThroughput / 1e6; // Convert bits per second to Mbps
}


double Wifi4Protocol::calculateLatency() {
    if (totalPacketsTransmitted == 0) return 0.0;
    double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
    return avgBackoffTime + 60.0;
}

double Wifi4Protocol::calculateMaxLatency() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> randomOffset(-1, 2); // Random offset in milliseconds (-10 to +20 ms)

    double maxBackoffTime = maxBackoffTimeRecorded + randomOffset(gen); // Add a random offset
    double transmissionTime = 60.0; // Fixed packet transmission time

    return maxBackoffTime + transmissionTime; // Total max latency
}


void Wifi4Protocol::resetMetrics() {
    totalBackoffTime = 0.0;
    maxBackoffTimeRecorded = 0.0;
    totalPacketsTransmitted = 0;
}
