#ifndef PACKET_H
#define PACKET_H

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

class DLL_EXPORT Packet {
public:
    Packet(int size);  // Constructor takes size in bytes
    ~Packet();  // Destructor

    int getSize() const;  // Get the size of the packet in bytes

private:
    int size;  // Packet size in bytes
};

#endif
