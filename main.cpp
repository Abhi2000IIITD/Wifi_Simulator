#include <iostream>
#include <vector>
#include "WiFiProtocols.h"
#include "AccessPoint.h"
#include "User.h"
#include "FrequencyChannel.h"

void runSimulation(int protocolChoice, int numUsers) {
    // Common setup for all protocols
    FrequencyChannel* channel = new FrequencyChannel(20); // 20 MHz bandwidth
    AccessPoint* ap = new AccessPoint(1, channel);        // AccessPoint with ID 1
    std::vector<User*> users;

    // Create users and add them to the AccessPoint
    for (int i = 0; i < numUsers; ++i) {
        User* user = new User(i + 1);
        // Add a dummy packet for each user
        user->addPacket(new Packet(1024, i + 1)); // 1 KB packets
        users.push_back(user);
        ap->connectUser(user);
    }

    WiFiProtocol* protocol = nullptr;

    // Choose the protocol based on the user's input
    switch (protocolChoice) {
    case 1: // WiFi4
        protocol = new WiFi4(ap);
        break;
    case 2: // WiFi5
        protocol = new WiFi5(ap, users);
        break;
    case 3: // WiFi6
        protocol = new WiFi6(ap, {2, 4, 10}); // Example subchannel allocations
        break;
    default:
        std::cout << "Invalid protocol choice!" << std::endl;
        return;
    }

    // Simulate and calculate metrics
    protocol->simulate();
    protocol->calculateMetrics();

    // Cleanup
    delete protocol;
    for (User* user : users) {
        delete user;
    }
    delete ap;
    delete channel;
}

int main() {
    int choice;
    do {
        std::cout << "\nWiFi Simulator\n";
        std::cout << "1. Simulate WiFi4 (CSMA/CA)\n";
        std::cout << "2. Simulate WiFi5 (MU-MIMO)\n";
        std::cout << "3. Simulate WiFi6 (OFDMA)\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 4) {
            std::cout << "Exiting simulation. Goodbye!\n";
            break;
        }

        // Run simulations for 1 user, 10 users, and 100 users
        for (int numUsers : {1, 10, 100}) {
            std::cout << "\nSimulating with " << numUsers << " user(s)...\n";
            runSimulation(choice, numUsers);
        }
    } while (choice != 4);

    return 0;
}
