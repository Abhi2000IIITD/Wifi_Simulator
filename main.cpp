#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>  // For exception handling
#include "AccessPoint.h"
#include "User.h"
#include "Packet.h"
#include "FrequencyChannel.h"
#include "WifiProtocol.h" // Includes the WifiProtocol, Wifi4Protocol, Wifi5Protocol, Wifi6Protocol, Wifi7Protocol classes

using namespace std;

// Define user counts globally, so it can be reused across the program
const int userCounts[] = {1, 10, 100}; // Define user counts for simulation
const size_t numUserCounts = sizeof(userCounts) / sizeof(userCounts[0]); // Calculate number of elements in userCounts array

// Custom exception class for invalid menu option
class InvalidMenuOptionException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid menu option. Please enter a valid option (1-5).";
    }
};

// Custom exception class for invalid user count input
class InvalidUserCountException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Invalid user count. Please enter a positive integer for the number of users.";
    }
};

// Function to validate user input for menu options
int getValidMenuOption() {
    int option;
    while (true) {
        cout << "Enter your option: ";
        cin >> option;

        if (cin.fail() || option < 1 || option > 5) {
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            throw InvalidMenuOptionException();
        }

        return option;
    }
}

// Function to validate user input for custom user count
int getValidUserCount() {
    int userCount;
    while (true) {
        cout << "Enter the total number of users: ";
        cin >> userCount;

        if (cin.fail() || userCount <= 0) {
            cin.clear();  // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
            throw InvalidUserCountException();
        }

        return userCount;
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));  // Seed random number generator for randomness

    int option;
    int customUserCount = 0;  // To store the custom user count if entered

    do {
        try {
            // Display menu and get valid option
            cout << "\n--- WiFi Simulator Menu ---\n";
            cout << "1) WiFi 4 Simulation\n";
            cout << "2) WiFi 5 Simulation\n";
            cout << "3) WiFi 6 Simulation\n";
            cout << "4) WiFi 7 Simulation\n";  // Add WiFi 7 option
            cout << "5) Exit\n";

            // Validate the menu option input
            option = getValidMenuOption();

            if (option == 5) {
                break; // Exit if the user chooses option 5 (Exit)
            }

            // Ask if the user wants to enter a custom user count only if the simulation option is selected
            char response = 'n'; // Default response
            if (option >= 1 && option <= 4) {
                cout << "\nDo you want to test with a custom number of users? (y/n): ";
                cin >> response;
            }

            if (response == 'y' || response == 'Y') {
                customUserCount = getValidUserCount();  // Get custom user input
            } else {
                customUserCount = 0;  // Reset to 0, meaning no custom user count
            }

            // Simulate based on the selected option
            if (option == 1) {
                cout << "\nStarting WiFi 4 Simulation...\n";
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
                // If custom user count is provided, simulate with that too
                if (customUserCount > 0) {
                    cout << "\nSimulating with custom " << customUserCount << " users...\n";
                    try {
                        Wifi4Protocol wifi4(customUserCount);
                        wifi4.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }

            } else if (option == 2) {
                cout << "\nStarting WiFi 5 Simulation...\n";
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
                // If custom user count is provided, simulate with that too
                if (customUserCount > 0) {
                    cout << "\nSimulating with custom " << customUserCount << " users...\n";
                    try {
                        Wifi5Protocol wifi5(customUserCount);
                        wifi5.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }

            } else if (option == 3) {
                cout << "\nStarting WiFi 6 Simulation...\n";
                for (size_t i = 0; i < numUserCounts; ++i) {
                    cout << "\nSimulating with " << userCounts[i] << " users...\n";
                    try {
                        // Instantiate and simulate Wifi6Protocol
                        Wifi6Protocol wifi6(userCounts[i]);
                        wifi6.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }
                // If custom user count is provided, simulate with that too
                if (customUserCount > 0) {
                    cout << "\nSimulating with custom " << customUserCount << " users...\n";
                    try {
                        Wifi6Protocol wifi6(customUserCount);
                        wifi6.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }

            } else if (option == 4) {
                cout << "\nStarting WiFi 7 Simulation...\n";
                for (size_t i = 0; i < numUserCounts; ++i) {
                    cout << "\nSimulating with " << userCounts[i] << " users...\n";
                    try {
                        // Instantiate and simulate Wifi7Protocol
                        Wifi7Protocol wifi7(userCounts[i]);
                        wifi7.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }
                // If custom user count is provided, simulate with that too
                if (customUserCount > 0) {
                    cout << "\nSimulating with custom " << customUserCount << " users...\n";
                    try {
                        Wifi7Protocol wifi7(customUserCount);
                        wifi7.startSimulation();
                    } catch (const exception &e) {
                        cout << "An error occurred during simulation: " << e.what() << "\n";
                    }
                }

            }

        } catch (const exception &e) {
            cout << "An error occurred: " << e.what() << "\n";
        }

    } while (option != 5); // Loop until option 5 (Exit) is chosen

    cout << "\nExiting the program.\n";
    return 0;
}
