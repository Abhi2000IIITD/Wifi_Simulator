#include "AccessPoint.h"
#include "User.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>  // Make sure this is included for std::remove

using namespace std;

AccessPoint::AccessPoint(int maxUsers) : maxUsers(maxUsers) {
    channel = new FrequencyChannel();
}

AccessPoint::~AccessPoint() {
    delete channel;
}

bool AccessPoint::isChannelFree() {
    return channel->isFree();
}

void AccessPoint::transmitPacket(User* user) {
    if (isChannelFree()) {
        channel->occupy();  // Mark channel as occupied
        // Simulate packet transmission logic (simplified for WiFi 4)
        // Packet transmission time is assumed to be 60ms
        this_thread::sleep_for(chrono::milliseconds(60));
        channel->free();  // Mark channel as free after transmission
    }
}

void AccessPoint::addUser(User* user) {
    if (users.size() < static_cast<size_t>(maxUsers)) {
        users.push_back(user);
    }
}

void AccessPoint::removeUser(User* user) {
    users.erase(std::remove(users.begin(), users.end(), user), users.end()); // Use std::remove explicitly
}

double AccessPoint::calculateThroughput() {
    // Simple throughput calculation (example)
    return 100.0;  // Placeholder throughput value
}

double AccessPoint::calculateAverageLatency() {
    // Placeholder for average latency calculation
    return 50.0;  // Placeholder value
}

double AccessPoint::calculateMaxLatency() {
    // Placeholder for max latency calculation
    return 100.0;  // Placeholder value
}
