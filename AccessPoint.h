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

// Add the forward declaration at the top
class User;

class DLL_EXPORT AccessPoint {
public:
    AccessPoint(int maxUsers);
    ~AccessPoint();

    bool isChannelFree();  // Check if the channel is free
    void transmitPacket(User* user);  // Simulate transmission from a user
    void addUser(User* user);  // Add user to the AP
    void removeUser(User* user);  // Remove user from AP
    
    // Add declarations for the missing functions
    int getCurrentUsersCount() const;  // Declare the method to get the current user count
    FrequencyChannel* getChannel() const;  // Declare the method to get the channel object

private:
    FrequencyChannel* channel;
    std::vector<User*> users;  // List of users connected to the AP
    int maxUsers;
};


#endif
