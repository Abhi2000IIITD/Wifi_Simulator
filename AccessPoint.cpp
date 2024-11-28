#include "AccessPoint.h"
#include "User.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>

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

// Define the methods in AccessPoint.cpp

int AccessPoint::getCurrentUsersCount() const {
    return users.size();  // Returns the number of users currently connected to the AP
}

FrequencyChannel* AccessPoint::getChannel() const {
    return channel;  // Returns the current frequency channel
}
