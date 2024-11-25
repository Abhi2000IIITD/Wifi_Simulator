#include "WiFiProtocols.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds


// Utility for random backoff
double getRandomBackoff(double maxBackoff) {
    static std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(0.0, maxBackoff);
    return distribution(generator);
}

// --- WiFi4 Implementation ---
WiFi4::WiFi4(AccessPoint* ap) : ap(ap), backoffTime(0.0) {}

void WiFi4::simulate() {
    std::cout << "Simulating WiFi4 (CSMA/CA)..." << std::endl;
    const double maxBackoffTime = 10.0; // Max backoff in ms

    for (User* user : ap->getConnectedUsers()) {
        Packet* packet = user->getNextPacket();
        while (packet) {
            if (ap->getChannel()->checkIfFree()) {
                ap->getChannel()->occupyChannel();
                ap->transmitPacket(packet, user);
                ap->getChannel()->releaseChannel();
            } else {
                backoffTime = getRandomBackoff(maxBackoffTime);
                std::cout << "Backoff time: " << backoffTime << " ms for User " << user->getUserID() << std::endl;
            }
            packet = user->getNextPacket();
        }
    }
}

void WiFi4::calculateMetrics() {
    std::cout << "Calculating WiFi4 metrics..." << std::endl;
    double throughput = ap->calculateThroughput();
    double avgLatency = ap->calculateAverageLatency();
    double maxLatency = ap->calculateMaxLatency();

    std::cout << "WiFi4 Metrics:" << std::endl;
    std::cout << "Throughput: " << throughput << " Mbps" << std::endl;
    std::cout << "Average Latency: " << avgLatency << " ms" << std::endl;
    std::cout << "Maximum Latency: " << maxLatency << " ms" << std::endl;
}

// --- WiFi5 Implementation ---
WiFi5::WiFi5(AccessPoint* ap, const std::vector<User*>& users)
    : ap(ap), users(users) {}

void WiFi5::simulate() {
    std::cout << "Simulating WiFi5 (MU-MIMO)..." << std::endl;

    // Simulate CSI exchange
    for (User* user : users) {
        Packet* csiPacket = new Packet(200, user->getUserID()); // CSI packet size 200 bytes
        ap->transmitPacket(csiPacket, user);
        delete csiPacket;
    }

    // Simulate parallel communication
    const double parallelTransmissionTime = 15.0; // 15 ms
    std::cout << "Parallel transmission for " << parallelTransmissionTime << " ms." << std::endl;

    for (User* user : users) {
        Packet* dataPacket = user->getNextPacket();
        if (dataPacket) {
            ap->transmitPacket(dataPacket, user);
        }
    }

    // Simulate the 15 ms transmission delay
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(parallelTransmissionTime)));
}

void WiFi5::calculateMetrics() {
    std::cout << "Calculating WiFi5 metrics..." << std::endl;
    double throughput = ap->calculateThroughput();
    double avgLatency = ap->calculateAverageLatency();
    double maxLatency = ap->calculateMaxLatency();

    std::cout << "WiFi5 Metrics:" << std::endl;
    std::cout << "Throughput: " << throughput << " Mbps" << std::endl;
    std::cout << "Average Latency: " << avgLatency << " ms" << std::endl;
    std::cout << "Maximum Latency: " << maxLatency << " ms" << std::endl;
}

// --- WiFi6 Implementation ---
WiFi6::WiFi6(AccessPoint* ap, const std::vector<int>& subChannelAllocations)
    : ap(ap), subChannelAllocations(subChannelAllocations) {}

void WiFi6::simulate() {
    std::cout << "Simulating WiFi6 (OFDMA)..." << std::endl;

    const double transmissionTime = 5.0; // Sub-channel usage for 5 ms
    for (size_t i = 0; i < subChannelAllocations.size(); ++i) {
        std::cout << "Allocating " << subChannelAllocations[i] << " MHz to sub-channel " << i << "." << std::endl;
        Packet* packet = ap->getConnectedUsers()[i]->getNextPacket();
        if (packet) {
            ap->transmitPacket(packet, ap->getConnectedUsers()[i]);
        }
    }

    // Simulate the 5 ms transmission time
    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(transmissionTime)));
}

void WiFi6::calculateMetrics() {
    std::cout << "Calculating WiFi6 metrics..." << std::endl;
    double throughput = ap->calculateThroughput();
    double avgLatency = ap->calculateAverageLatency();
    double maxLatency = ap->calculateMaxLatency();

    std::cout << "WiFi6 Metrics:" << std::endl;
    std::cout << "Throughput: " << throughput << " Mbps" << std::endl;
    std::cout << "Average Latency: " << avgLatency << " ms" << std::endl;
    std::cout << "Maximum Latency: " << maxLatency << " ms" << std::endl;
}
