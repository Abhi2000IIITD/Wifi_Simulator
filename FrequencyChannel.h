#ifndef FREQUENCYCHANNEL_H
#define FREQUENCYCHANNEL_H

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT FrequencyChannel {
public:
    FrequencyChannel();
    bool isFree();  // Check if the channel is free
    void occupy();  // Mark the channel as occupied
    void free();    // Mark the channel as free

private:
    bool channelOccupied;  // Track channel occupancy
};

#endif
