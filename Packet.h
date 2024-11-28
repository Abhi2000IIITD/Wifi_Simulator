#ifndef PACKET_H
#define PACKET_H

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#elif defined(USE_DLL)
#define DLL_EXPORT __declspec(dllimport)
#else
#define DLL_EXPORT
#endif

// Template definition for Packet class
template <typename T>
class DLL_EXPORT Packet {
public:
    // Constructor takes the size in bytes (generic for any type T)
    Packet(int size);  
    ~Packet();  // Destructor

    // Get the size of the packet in bytes
    int getSize() const;  

private:
    int size;  // Packet size in bytes (this can vary depending on the type T)
    T* data;   // Pointer to data of type T
};
template class DLL_EXPORT Packet<int>;       
template class DLL_EXPORT Packet<float>;     

#endif
