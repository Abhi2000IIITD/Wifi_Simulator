#include "User.h"
#include "AccessPoint.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

User::User(int id) : userId(id), packet(new Packet<int>(1024)) {  // Specify template argument
    srand(time(0));  // Seed random number generator
}

User::~User() {
    delete packet;
}

void User::attemptTransmission() {
    // Simulate transmission attempt
    AccessPoint* ap = nullptr;  // Placeholder: Ideally, access point should be passed in constructor
    if (ap != nullptr && ap->isChannelFree()) {
        ap->transmitPacket(this);
    }
}

void User::backoff(double maxBackoffTime) {
    // Random backoff time between 0 and maxBackoffTime
    backoffTime = (rand() % (int)(maxBackoffTime * 1000)) / 1000.0;  // Random time in seconds
}

int User::getId() const {
    return userId;
}