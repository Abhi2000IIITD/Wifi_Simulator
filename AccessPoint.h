#ifndef ACCESSPOINT_H
#define ACCESSPOINT_H

#include "User.h"
#include "FrequencyChannel.h"
#include <vector>
#include <ctime>
#include <cstdlib>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT AccessPoint {
public:
    AccessPoint(int maxUsers);
    ~AccessPoint();

    bool isChannelFree();  // Check if the channel is free
    void transmitPacket(User* user);  // Simulate transmission from a user
    void addUser(User* user);  // Add user to the AP
    void removeUser(User* user);  // Remove user from AP


private:
    FrequencyChannel* channel;
    std::vector<User*> users;
    int maxUsers;
};

#endif
