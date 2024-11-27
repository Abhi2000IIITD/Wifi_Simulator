#ifndef USER_H
#define USER_H

#include "Packet.h"
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
    User(int id);
    ~User();

    void attemptTransmission();  // Try transmitting packet
    void backoff(double maxBackoffTime);  // Handle backoff behavior
    int getId() const;
    Packet* getPacket() const { return packet; }
    double getBackoffTime() const { return backoffTime; }

private:
    int userId;
    Packet* packet;
    double backoffTime;  // Random backoff time
};

#endif
