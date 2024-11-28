#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AccessPoint.h"
#include "User.h"
#include "Packet.h"
#include "FrequencyChannel.h"
#include "WifiProtocol.h" // Includes the WifiProtocol, Wifi4Protocol, Wifi5Protocol, Wifi6Protocol, Wifi7Protocol classes

using namespace std;

// Define user counts globally, so it can be reused across the program
const int userCounts[] = {1, 10, 100}; // Define user counts for simulation
const size_t numUserCounts = sizeof(userCounts) / sizeof(userCounts[0]); // Calculate number of elements in userCounts array

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator for randomness

    int option;
    do {
        cout << "\n--- WiFi Simulator Menu ---\n";
        cout << "1) WiFi 4 Simulation\n";
        cout << "2) WiFi 5 Simulation\n";
        cout << "3) WiFi 6 Simulation\n";
        cout << "4) WiFi 7 Simulation\n";  // Add WiFi 7 option
        cout << "5) Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1) {
            cout << "\nStarting WiFi 4 Simulation for different user counts...\n";
            for (size_t i = 0; i < numUserCounts; ++i) {
                cout << "\nSimulating with " << userCounts[i] << " users...\n";
                try {
                    // Instantiate and simulate Wifi4Protocol
                    Wifi4Protocol wifi4(userCounts[i]);
                    wifi4.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option == 2) {
            cout << "\nStarting WiFi 5 Simulation for different user counts...\n";
            for (size_t i = 0; i < numUserCounts; ++i) {
                cout << "\nSimulating with " << userCounts[i] << " users...\n";
                try {
                    // Instantiate and simulate Wifi5Protocol
                    Wifi5Protocol wifi5(userCounts[i]);
                    wifi5.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option == 3) {
            cout << "\nStarting WiFi 6 Simulation for different user counts...\n";
            for (size_t i = 0; i < numUserCounts; ++i) {
                cout << "\nSimulating with " << userCounts[i] << " users...\n";
                try {
                    // Instantiate and simulate Wifi6Protocol
                    Wifi6Protocol wifi6(userCounts[i]);  // Assume Wifi6Protocol constructor accepts userCount as a parameter
                    wifi6.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option == 4) {
            cout << "\nStarting WiFi 7 Simulation for different user counts...\n";
            for (size_t i = 0; i < numUserCounts; ++i) {
                cout << "\nSimulating with " << userCounts[i] << " users...\n";
                try {
                    // Instantiate and simulate Wifi7Protocol
                    Wifi7Protocol wifi7(userCounts[i]);  // Assume Wifi7Protocol constructor accepts userCount as a parameter
                    wifi7.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option != 5) {
            cout << "\nInvalid option. Please try again.\n";
        }

    } while (option != 5); // Loop until option 5 (Exit) is chosen

    cout << "\nExiting the program.\n";
    return 0;
}
