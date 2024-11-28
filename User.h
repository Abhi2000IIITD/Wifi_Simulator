#ifndef USER_H
#define USER_H

#include "Packet.h"
#include "AccessPoint.h"
#include <cstdlib>
#include <ctime>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT User {
public:
    User(int id);  // Constructor that takes an integer ID
    ~User();

    void attemptTransmission();  // Try transmitting packet
    void backoff(double maxBackoffTime);  // Handle backoff behavior
    int getId() const;

    // Get the packet with the template argument explicitly specified
    Packet<int>* getPacket() const { return packet; }  // Explicit template argument for Packet<int>

private:
    int userId;  // Declare the user ID first
    Packet<int>* packet;  // Declare packet pointer of type Packet<int>
    double backoffTime;  // Random backoff time
};

#endif
