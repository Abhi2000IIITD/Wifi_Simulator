#include "FrequencyChannel.h"

FrequencyChannel::FrequencyChannel() : channelOccupied(false) {}

bool FrequencyChannel::isFree() {
    return !channelOccupied;
}

void FrequencyChannel::occupy() {
    channelOccupied = true;
}

void FrequencyChannel::free() {
    channelOccupied = false;
}
