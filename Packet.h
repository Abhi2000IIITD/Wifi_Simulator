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
    Packet(int size);
    ~Packet();

    int getSize() const;

private:
    int size;  // Packet size in bytes
};

#endif
