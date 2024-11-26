#include <iostream>
#include "AccessPoint.h"
#include "User.h"
#include "Packet.h"
#include "FrequencyChannel.h"
#include "WifiProtocol.h" // Includes the WifiProtocol and Wifi4Protocol classes

using namespace std;

int main() {
    srand(time(0));  // Seed random number generator for backoff time

    int option;
    do {
        cout << "\n--- WiFi Simulator Menu ---\n";
        cout << "1) WiFi 4 Simulation\n";
        cout << "2) Exit\n";
        cout << "Enter your option: ";
        cin >> option;

        if (option == 1) {
            cout << "\nStarting WiFi 4 Simulation for different user counts...\n";
            int userCounts[] = {1, 10, 100}; // Define user counts for simulation

            for (int count : userCounts) {
                cout << "\nSimulating with " << count << " users...\n";
                // Instantiate and simulate Wifi4Protocol
                Wifi4Protocol wifi4(count);
                wifi4.startSimulation();
            }
        } else if (option != 2) {
            cout << "\nInvalid option. Please try again.\n";
        }

    } while (option != 2); // Loop until option 2 (Exit) is chosen

    cout << "\nExiting the program. Goodbye!\n";
    return 0;
}
