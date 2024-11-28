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
        //cout << "User " << i + 1 << " backoff time: " << backoffTime << " ms\n";
    }

    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}

double Wifi4Protocol::calculateThroughput() {
    double bandwidth = 20.0;                // MHz
    double modulationEfficiency = 6.0;     // Bits per symbol for 256-QAM with 5/6 coding rate
    double packetSize = 8192.0;             // 1 KB packet size in bits
    double transmissionTime = 60.0 / 1000; // 60 ms in seconds

    // Random factor to simulate real-world variability
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> randomFactor(0.8, 1.0); // Random factor between 0.8 and 1.0

    double throughputPerUser = (packetSize / transmissionTime) * modulationEfficiency;
    double randomBandwidth = bandwidth * randomFactor(gen);  // Randomized bandwidth
    double totalThroughput = (randomBandwidth / userCount) * throughputPerUser; // Adjust throughput

    return totalThroughput / 1e6; // Convert bits per second to Mbps
}


double Wifi4Protocol::calculateLatency() {
    if (totalPacketsTransmitted == 0) return 0.0;
    
    if (userCount == 1) { // Special case for 1 user
        double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
        return avgBackoffTime; // Backoff time + fixed transmission time
    }
    
    // Default case for multiple users
    double avgBackoffTime = totalBackoffTime / totalPacketsTransmitted;
    return avgBackoffTime;
}

double Wifi4Protocol::calculateMaxLatency() {
    if (userCount == 1) { // Special case for 1 user
        return calculateLatency(); // Max latency = Average latency
    }
    
    // Default case for multiple users
    double maxBackoffTime = maxBackoffTimeRecorded; // Maximum backoff time
    return maxBackoffTime; // Backoff time + fixed transmission time
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
    const double broadcastTime = 2.0; // Fixed 2 ms for broadcast
    const double csiPacketTimePerUser = 0.1; // 0.1 ms per user for CSI packet
    const double parallelTransmissionTime = 15.0; // Parallel transmission time (ms)
    const double bandwidth = 20.0; // MHz
    const double modulationEfficiency = 6.0; // 256-QAM with 5/6 coding rate
    const double dataRatePerUser = (bandwidth / userCount) * modulationEfficiency; // Per user Mbps

    int remainingUsers = userCount;

    resetMetrics();

    cout << "Starting WiFi 5 simulation with " << userCount << " users.\n";

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> csiRandomFactor(0.9, 1.1); // Variability in CSI time
    
    while (remainingUsers > 0) {
        int usersInRound;

        // Step 1: Randomly determine users sending CSI
        if (remainingUsers > userCount * 0.1) { // Random portion
            uniform_int_distribution<> dist(1, remainingUsers);
            usersInRound = dist(gen);
        } else { // Include all remaining users
            usersInRound = remainingUsers;
        }

        remainingUsers -= usersInRound;

        // Step 2: Calculate times for this round
        double csiPhaseTime = usersInRound * csiPacketTimePerUser * csiRandomFactor(gen);
        double totalRoundTime = broadcastTime + csiPhaseTime + parallelTransmissionTime;

        // Step 3: Calculate data transmitted
        double dataTransmitted = usersInRound * dataRatePerUser * (parallelTransmissionTime / 1000.0);

        // Update total metrics
        totalTime += totalRoundTime;
        totalDataTransmitted += dataTransmitted;
        maxLatency = max(maxLatency, totalRoundTime);
        totalRounds++;
        AccessPoint* ap = new AccessPoint(100);  // Create AccessPoint with max 100 users
        User* user = new User(1); 
        ap->transmitPacket(user);

        // Output details for this round
        cout << fixed << setprecision(2); // Set output precision for clarity
        cout << "Round " << totalRounds << ": " << usersInRound << " users participated.\n";
    }

    // Final metrics
    cout << "WiFi 5 Simulation Results:\n";
    cout << "Throughput: " << calculateThroughput() << " Mbps\n";
    cout << "Average Latency: " << calculateLatency() << " ms\n";
    cout << "Max Latency: " << calculateMaxLatency() << " ms\n";
}


double Wifi5Protocol::calculateThroughput() {
    return totalDataTransmitted / (totalTime / 1000.0); // Mbps
}

double Wifi5Protocol::calculateLatency() {
    if (totalRounds == 0) return 0; // Prevent division by zero if no rounds
    return totalTime / totalRounds; // Average round latency in ms
}

double Wifi5Protocol::calculateMaxLatency() {
    return maxLatency; // Maximum total time for any round
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


// Calculate Average Latency: Average latency for all users
double Wifi6Protocol::calculateAverageLatency() {
    double sumLatencies = 0;
    for (double latency : userLatencies) {
        sumLatencies += latency;
    }
    return userLatencies.empty() ? 0 : sumLatencies / userLatencies.size();
}

// Calculate Max Latency: Max latency for all users
double Wifi6Protocol::calculateMaxLatency() {
    // Base max latency factor: 5ms per 10 users
    double baseMaxLatency = 5 * (numUsers / 10);  // 5ms per 10 users (rounds)

    // Return the final calculated max latency (no cap)
    return baseMaxLatency;
}

double simulateDataTransmitted(int round) {
    // Example: Simulate data transmitted in bits (adjust logic as needed)
    return 1e6 * round;  // 1 Mbps per round for simplicity
}

double simulateTransmissionTime(int round) {
    // Example: Simulate time taken in seconds (adjust logic as needed)
    return 0.1 * round;  // 0.1 seconds per round for simplicity
}

// Start the Simulation: Calculate latency and throughput for each user
void Wifi6Protocol::startSimulation() {
    // Reset metrics at the start of each simulation
    resetMetrics();

    double totalLatency = 0;
    double totalThroughputPerUser = 0;

    // Define the number of subchannels (10 in this case)
    int numSubchannels = 10;
    
    // Ensure we have enough subchannels for all users, if not, you can scale to more rounds
    int numRounds = (numUsers + numSubchannels - 1) / numSubchannels;  // Round up if users are not exactly divisible by subchannels

    for (int round = 1; round <= numRounds; ++round) {
        int startIdx = (round - 1) * numSubchannels; // Calculate start user index for this round
        int endIdx = std::min(startIdx + numSubchannels, numUsers); // Ensure we don't exceed total users

        // Simulate the transmission for each subchannel in the round
        for (int subchannel = startIdx; subchannel < endIdx; ++subchannel) {
            // Simulate data transmitted and total time for the user in the current subchannel
            double dataTransmitted = simulateDataTransmitted(subchannel + 1);  // Example: bits (user index is subchannel + 1)
            double totalTime = simulateTransmissionTime(subchannel + 1);       // Example: seconds

            // Calculate latency for the current user in the subchannel
            double latency = calculateLatencyForRound(subchannel + 1);

            // Calculate throughput for the current user in the subchannel
            double throughput = calculateThroughput(dataTransmitted, totalTime);

            // Store latencies for averaging
            userLatencies.push_back(latency);

            // Accumulate total latency and throughput
            totalLatency += latency;
            totalThroughputPerUser += throughput;
        }
    }

    // Calculate average latency and average throughput per user
    double avgLatency = totalLatency / numUsers;
    double avgThroughputPerUser = totalThroughputPerUser / numUsers;

    // Print simulation results
    std::cout << "System Throughput: " << avgThroughputPerUser << " Mbps" << std::endl;
    std::cout << "Average Latency: " << avgLatency << " ms" << std::endl;
    std::cout << "Maximum Latency: " << calculateMaxLatency() << " ms" << std::endl;
}


// Reset Metrics: Reset all metrics for the WiFi 6 simulation
void Wifi6Protocol::resetMetrics() {
    // Reset the metrics for the WiFi 6 simulation
    totalDataTransmitted = 0;
    maxLatency = 0;
    totalTime = 0;
    userLatencies.clear();
}
//=====================================================================================================
// Constructor to initialize Wifi7Protocol
Wifi7Protocol::Wifi7Protocol(int userCount) 
    : userCount(userCount), totalBandwidth(6000.0), modulationEfficiency(10.0), packetSize(8192.0) { // Example values
    // Here 6000 Mbps is the total available bandwidth for WiFi 7
    // 10 is the modulation efficiency for 4096-QAM (can be adjusted based on modulation)
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator
}

// Start the WiFi 7 simulation
void Wifi7Protocol::startSimulation() {
    cout << "Starting WiFi 7 simulation with " << userCount << " users.\n";

    double throughput = calculateThroughput();
    double avgLatency = calculateLatency();
    double maxLatency = calculateMaxLatency();

    cout << "Throughput: " << throughput << " Mbps\n";
    cout << "Average Latency: " << avgLatency << " ms\n";
    cout << "Max Latency: " << maxLatency << " ms\n";
}

// Calculate the throughput in Mbps based on the number of users
double Wifi7Protocol::calculateThroughput() {
    // Adjust throughput per user based on total bandwidth and user count
    double throughputPerUser = calculateRealTimeThroughput(userCount);

    // Add some random variation to the throughput
    double randomFactor = generatePacket(0.9, 1.1);  // 10% random variation
    return throughputPerUser * randomFactor;
}

// Calculate average latency in ms based on the number of users
double Wifi7Protocol::calculateLatency() {
    // Add some random variation to the latenc
    double baseLatency = calculateRealTimeLatency(userCount);  
    return baseLatency;
}

// Calculate maximum latency in ms based on the number of users
double Wifi7Protocol::calculateMaxLatency() {
    // Add some random variation to the max latency
    double baseMaxLatency = calculateRealTimeLatency(userCount) * 1.5;
    return baseMaxLatency;
}

// Helper function to calculate throughput per user based on the number of users
double Wifi7Protocol::calculateRealTimeThroughput(int userCount) {
    // The total bandwidth is shared among all users
    double availableBandwidthPerUser = totalBandwidth / userCount;  // Mbps per user
    
    // Adjust throughput with modulation efficiency (simplified)
    double throughput = availableBandwidthPerUser * modulationEfficiency;
    
    return throughput;
}

// Helper function to calculate average latency based on the number of users
double Wifi7Protocol::calculateRealTimeLatency(int userCount) {
    // Latency increases with more users
    double baseLatency = 1.0;  // Base latency in ms for 1 user
    double userLatencyImpact = 0.1 * userCount;  // Latency impact per user

    return baseLatency + userLatencyImpact;  // Total latency in ms
}

// Function to generate a random factor for variability
double Wifi7Protocol::generatePacket(double lower, double upper) {
    // Generate a random number between lower and upper
    return lower + (rand() / (RAND_MAX / (upper - lower)));
}
