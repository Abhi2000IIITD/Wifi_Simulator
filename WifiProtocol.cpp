#include "WifiProtocol.h"
#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "User.h"

using namespace std;

Wifi4Protocol::Wifi4Protocol(int userCount, int maxBackoffTime)
    : userCount(userCount), maxBackoffTime(maxBackoffTime) {
    resetMetrics();
}

void Wifi4Protocol::startSimulation() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxBackoffTime);

    cout << "Starting WiFi 4 simulation with " << userCount << " users.\n";

    for (int i = 0; i < userCount; ++i) {
        double backoffTime = dist(gen);
        totalBackoffTime += backoffTime;
        totalPacketsTransmitted++;
        maxBackoffTimeRecorded = max(maxBackoffTimeRecorded, backoffTime);
    }

    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double Wifi4Protocol::calculateThroughput() {
    double bandwidth = 20.0;                
    double modulationEfficiency = 6.0;     
    double packetSize = 8192.0;             
    double transmissionTime = 60.0 / 1000; 
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> randomFactor(0.8, 1.0);

    double throughputPerUser = (packetSize / transmissionTime) * modulationEfficiency;
    double randomBandwidth = bandwidth * randomFactor(gen); 
    double totalThroughput = (randomBandwidth / userCount) * throughputPerUser; 

    return totalThroughput / 1e6;
}
double Wifi4Protocol::calculateLatency() {
    if (totalPacketsTransmitted == 0) return 0.0;
    
    if (userCount == 1) { 
        double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
        return avgBackoffTime; 
    }
    double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
    return avgBackoffTime;
}

double Wifi4Protocol::calculateMaxLatency() {
    if (userCount == 1) { 
        return calculateLatency(); 
    }
    
    // Default case for multiple users
    double maxBackoffTime = maxBackoffTimeRecorded; 
    return maxBackoffTime; 
}


void Wifi4Protocol::resetMetrics() {
    totalBackoffTime = 0.0;
    maxBackoffTimeRecorded = 0.0;
    totalPacketsTransmitted = 0;
}

//================================================================================================
Wifi5Protocol::Wifi5Protocol(int userCount)
    : userCount(userCount), totalTime(0.0), totalDataTransmitted(0.0), totalRounds(0), maxLatency(0.0) {}

void Wifi5Protocol::resetMetrics() {
    totalTime = 0.0;
    totalDataTransmitted = 0.0;
    totalRounds = 0;
    maxLatency = 0.0;
}

void Wifi5Protocol::startSimulation() {
    const double broadcastTime = 2.0; 
    const double csiPacketTimePerUser = 0.1; 
    const double parallelTransmissionTime = 15.0; 
    const double bandwidth = 20.0; 
    const double modulationEfficiency = 6.0; 
    const double dataRatePerUser = (bandwidth / userCount) * modulationEfficiency;

    int remainingUsers = userCount;

    resetMetrics();

    cout << "Starting WiFi 5 simulation with " << userCount << " users.\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> csiRandomFactor(0.9, 1.1); // Variability in CSI time
    
    while (remainingUsers > 0) {
        int usersInRound;
        if (remainingUsers > userCount * 0.1) { 
            uniform_int_distribution<> dist(1, remainingUsers);
            usersInRound = dist(gen);
        } else { 
            usersInRound = remainingUsers;
        }
        remainingUsers -= usersInRound;
        double csiPhaseTime = usersInRound * csiPacketTimePerUser * csiRandomFactor(gen);
        double totalRoundTime = broadcastTime + csiPhaseTime + parallelTransmissionTime;
        double dataTransmitted = usersInRound * dataRatePerUser * (parallelTransmissionTime / 1000.0);
        totalTime += totalRoundTime;
        totalDataTransmitted += dataTransmitted;
        maxLatency = max(maxLatency, totalRoundTime);
        totalRounds++;
        AccessPoint* ap = new AccessPoint(100);
        User* user = new User(1); 
        ap->transmitPacket(user);
        cout << fixed << setprecision(2);
        cout << "Round " << totalRounds << ": " << usersInRound << " users participated.\n";
    }
    cout << "WiFi 5 Simulation Results:\n";
    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}


double Wifi5Protocol::calculateThroughput() {
    return totalDataTransmitted / (totalTime / 1000.0); // Mbps
}

double Wifi5Protocol::calculateLatency() {
    if (totalRounds == 0) return 0; 
    return totalTime / totalRounds;
}
double Wifi5Protocol::calculateMaxLatency() {
    return maxLatency; 
}


//==================================================================================================
Wifi6Protocol::Wifi6Protocol(int userCount) : numUsers(userCount), totalDataTransmitted(0), maxLatency(0), totalTime(0) {}

double Wifi6Protocol::calculateLatency() {
   
    return calculateLatencyForRound(numUsers);  
}

double Wifi6Protocol::calculateLatencyForRound(int round) {
 
    double baseLatency = 10 + (round / 10) * 5; 
    double randomVariation = rand() % 10 + 1; 
    return baseLatency + randomVariation;
}

double Wifi6Protocol::calculateThroughput() {
    double defaultDataTransmitted = 1e6;  
    double defaultTime = 1.0;

    return calculateThroughput(defaultDataTransmitted, defaultTime);
}

double Wifi6Protocol::calculateThroughput(double dataTransmitted, double totalTime) {
    if (totalTime <= 0 || numUsers <= 0) {
        throw std::invalid_argument("Total time and number of users must be positive");
    }
    double baseThroughput = dataTransmitted / totalTime; // bits per second
    baseThroughput = (baseThroughput / 1e6) * 1.25;
    double cap = 3.0; 
    double systemThroughput = baseThroughput / std::min(1.0 + 0.01 * (numUsers - 1), cap);
    systemThroughput = std::max(systemThroughput, 250.0);
    double throughputPerUser = systemThroughput / numUsers;
    double randomFactor = throughputPerUser * ((rand() % 31 - 15) / 100.0);
    throughputPerUser += randomFactor;
    return throughputPerUser;
}
double Wifi6Protocol::calculateAverageLatency() {
    double sumLatencies = 0;
    for (double latency : userLatencies) {
        sumLatencies += latency;
    }
    return userLatencies.empty() ? 0 : sumLatencies / userLatencies.size();
}
double Wifi6Protocol::calculateMaxLatency() {

    double baseMaxLatency = 5 * (numUsers / 10); 
    return baseMaxLatency;
}

double simulateDataTransmitted(int round) {
    return 1e6 * round;  
}

double simulateTransmissionTime(int round) {
    return 0.1 * round;  
}
void Wifi6Protocol::startSimulation() {

    resetMetrics();

    double totalLatency = 0;
    double totalThroughputPerUser = 0;
    int numSubchannels = 10;

    int numRounds = (numUsers + numSubchannels - 1) / numSubchannels;  

    for (int round = 1; round <= numRounds; ++round) {
        int startIdx = (round - 1) * numSubchannels;
        int endIdx = std::min(startIdx + numSubchannels, numUsers); 
        for (int subchannel = startIdx; subchannel < endIdx; ++subchannel) {
       
            double dataTransmitted = simulateDataTransmitted(subchannel + 1);
            double totalTime = simulateTransmissionTime(subchannel + 1);   
            double latency = calculateLatencyForRound(subchannel + 1);
            double throughput = calculateThroughput(dataTransmitted, totalTime);
            userLatencies.push_back(latency);
            totalLatency += latency;
            totalThroughputPerUser += throughput;
        }
    }
    double avgLatency = totalLatency / numUsers;
    double avgThroughputPerUser = totalThroughputPerUser / numUsers;
    std::cout << "System Throughput: " << avgThroughputPerUser << " Mbps" << std::endl;
    std::cout << "Average Latency: " << avgLatency << " ms" << std::endl;
    std::cout << "Maximum Latency: " << calculateMaxLatency() << " ms" << std::endl;
}

void Wifi6Protocol::resetMetrics() {
    totalDataTransmitted = 0;
    maxLatency = 0;
    totalTime = 0;
    userLatencies.clear();
}
//=====================================================================================================
// Constructor to initialize Wifi7Protocol
Wifi7Protocol::Wifi7Protocol(int userCount) 
    : userCount(userCount), totalBandwidth(6000.0), modulationEfficiency(10.0), packetSize(8192.0) { 
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
}
void Wifi7Protocol::startSimulation() {
    cout << "Starting WiFi 7 simulation with " << userCount << " users.\n";

    double throughput = calculateThroughput();
    double avgLatency = calculateLatency();
    double maxLatency = calculateMaxLatency();

    cout << "Throughput: " << throughput << " Mbps\n";
    cout << "Average Latency: " << avgLatency << " ms\n";
    cout << "Max Latency: " << maxLatency << " ms\n";
}
double Wifi7Protocol::calculateThroughput() {
    double throughputPerUser = calculateRealTimeThroughput(userCount);
    double randomFactor = generatePacket(0.9, 1.1);
    return throughputPerUser * randomFactor;
}
double Wifi7Protocol::calculateLatency() {
    double baseLatency = calculateRealTimeLatency(userCount);  
    return baseLatency;
}
double Wifi7Protocol::calculateMaxLatency() {
    double baseMaxLatency = calculateRealTimeLatency(userCount) * 1.5;
    return baseMaxLatency;
}
double Wifi7Protocol::calculateRealTimeThroughput(int userCount) {
    double availableBandwidthPerUser = totalBandwidth / userCount; 
    double throughput = availableBandwidthPerUser * modulationEfficiency;
    return throughput;
}
double Wifi7Protocol::calculateRealTimeLatency(int userCount) {
    double baseLatency = 1.0;  
    double userLatencyImpact = 0.1 * userCount; 

    return baseLatency + userLatencyImpact; 
}
double Wifi7Protocol::generatePacket(double lower, double upper) {
    return lower + (rand() / (RAND_MAX / (upper - lower)));
}
