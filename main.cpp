#include <iostream>
#include <cstdlib>
#include <ctime>
#include "AccessPoint.h"
#include "User.h"
#include "Packet.h"
#include "FrequencyChannel.h"
#include "WifiProtocol.h" // Includes the WifiProtocol, Wifi4Protocol, Wifi5Protocol, and Wifi6Protocol classes

using namespace std;

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator for randomness

    int option;
    do {
        cout << "\n--- WiFi Simulator Menu ---\n";
        cout << "1) WiFi 4 Simulation\n";
        cout << "2) WiFi 5 Simulation\n";
        cout << "3) WiFi 6 Simulation\n";  // Added WiFi 6 option
        cout << "4) Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1) {
            cout << "\nStarting WiFi 4 Simulation for different user counts...\n";
            int userCounts[] = {1, 10, 100}; // Define user counts for simulation

            for (int count : userCounts) {
                cout << "\nSimulating with " << count << " users...\n";
                try {
                    // Instantiate and simulate Wifi4Protocol
                    Wifi4Protocol wifi4(count);
                    wifi4.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option == 2) {
            cout << "\nStarting WiFi 5 Simulation for different user counts...\n";
            int userCounts[] = {1, 10, 100}; // Define user counts for simulation

            for (int count : userCounts) {
                cout << "\nSimulating with " << count << " users...\n";
                try {
                    // Instantiate and simulate Wifi5Protocol
                    Wifi5Protocol wifi5(count);
                    wifi5.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option == 3) {  // Added condition for WiFi 6
            cout << "\nStarting WiFi 6 Simulation for different user counts...\n";
            int userCounts[] = {1, 10, 100}; // Define user counts for simulation

            for (int count : userCounts) {
                cout << "\nSimulating with " << count << " users...\n";
                try {
                    // Instantiate and simulate Wifi6Protocol
                    Wifi6Protocol wifi6(count);
                    wifi6.startSimulation();
                } catch (const exception &e) {
                    cout << "An error occurred during simulation: " << e.what() << "\n";
                }
            }
        } else if (option != 4) {
            cout << "\nInvalid option. Please try again.\n";
        }

    } while (option != 4); // Loop until option 4 (Exit) is chosen

    cout << "\nExiting the program.\n";
    return 0;
}
