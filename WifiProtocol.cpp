#include "WifiProtocol.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>

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
    
    if (userCount == 1) { // Special case for 1 user
        double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
        return avgBackoffTime + 60.0; // Backoff time + fixed transmission time
    }
    
    // Default case for multiple users
    double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
    return avgBackoffTime + 60.0;
}

double Wifi4Protocol::calculateMaxLatency() {
    if (userCount == 1) { // Special case for 1 user
        return calculateLatency(); // Max latency = Average latency
    }
    
    // Default case for multiple users
    double maxBackoffTime = maxBackoffTimeRecorded; // Maximum backoff time
    return maxBackoffTime + 60.0; // Backoff time + fixed transmission time
}


void Wifi4Protocol::resetMetrics() {
    totalBackoffTime = 0.0;
    maxBackoffTimeRecorded = 0.0;
    totalPacketsTransmitted = 0;
}

//wifi 5 implementation begins here
Wifi5Protocol::Wifi5Protocol(int userCount)
    : userCount(userCount), totalTime(0.0), totalDataTransmitted(0.0), totalRounds(0), maxLatency(0.0) {}

void Wifi5Protocol::resetMetrics() {
    totalTime = 0.0;
    totalDataTransmitted = 0.0;
    totalRounds = 0;
    maxLatency = 0.0;
}

void Wifi5Protocol::startSimulation() {
    const double broadcastTime = 2.0; // Fixed 2 ms for broadcast
    const double csiPacketTimePerUser = 0.1; // 0.1 ms per user for CSI packet
    const double parallelTransmissionTime = 15.0; // Parallel transmission time (ms)
    const double bandwidth = 20.0; // MHz
    const double modulationEfficiency = 6.0; // 256-QAM with 5/6 coding rate
    const double dataRatePerUser = (bandwidth / userCount) * modulationEfficiency; // Per user Mbps

    int remainingUsers = userCount;

    resetMetrics();

    cout << "Starting WiFi 5 simulation with " << userCount << " users.\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> csiRandomFactor(0.9, 1.1); // Variability in CSI time

    while (remainingUsers > 0) {
        int usersInRound;

        // Step 1: Randomly determine users sending CSI
        if (remainingUsers > userCount * 0.1) { // Random portion
            uniform_int_distribution<> dist(1, remainingUsers);
            usersInRound = dist(gen);
        } else { // Include all remaining users
            usersInRound = remainingUsers;
        }

        remainingUsers -= usersInRound;

        // Step 2: Calculate times for this round
        double csiPhaseTime = usersInRound * csiPacketTimePerUser * csiRandomFactor(gen);
        double totalRoundTime = broadcastTime + csiPhaseTime + parallelTransmissionTime;

        // Step 3: Calculate data transmitted
        double dataTransmitted = usersInRound * dataRatePerUser * (parallelTransmissionTime / 1000.0);

        // Update total metrics
        totalTime += totalRoundTime;
        totalDataTransmitted += dataTransmitted;
        maxLatency = max(maxLatency, totalRoundTime);
        totalRounds++;

        // Output details for this round
        cout << fixed << setprecision(2); // Set output precision for clarity
        cout << "Round " << totalRounds << ": " << usersInRound << " users participated.\n";
    }

    // Final metrics
    cout << "WiFi 5 Simulation Results:\n";
    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}


double Wifi5Protocol::calculateThroughput() {
    return totalDataTransmitted / (totalTime / 1000.0); // Mbps
}

double Wifi5Protocol::calculateLatency() {
    return totalTime / userCount; // ms
}

double Wifi5Protocol::calculateMaxLatency() {
    return maxLatency; // Maximum total time for any round
}