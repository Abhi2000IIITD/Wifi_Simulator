# WiFi Simulator  

## Project Overview  
This project is a **WiFi Simulator** designed to model and simulate different WiFi communication protocols (WiFi 4, WiFi 5, and WiFi 6) under varying user and access point (AP) conditions. The simulator uses **object-oriented programming (OOP)** principles such as inheritance, data abstraction, data hiding, and polymorphism to ensure modularity and scalability.  

---

## Features  

### Core Components  

1. **Access Point (AccessPoint):**  
   - Manages users and their interactions with the communication channel.  
   - Handles packet transmissions and ensures channel availability.  

2. **Frequency Channel (FrequencyChannel):**  
   - Simulates the communication medium for data transmission.  
   - Tracks channel state (free/occupied).  

3. **User:**  
   - Represents a device attempting to transmit data via the access point.  
   - Implements random backoff logic to resolve collisions.  

4. **Packet:**  
   - Encapsulates data being transmitted.  
   - Tracks packet size and ensures proper memory management.  

5. **WiFi Protocols:**  
   - **Base Class (`WifiProtocol`):**  
     Provides an abstract interface for different WiFi protocol implementations.  

   - **Derived Protocols:**  
     - **WiFi 4:** Single access point communication with backoff-based collision resolution.  
     - **WiFi 5:** Supports parallel communication using multi-user MIMO.  
     - **WiFi 6:** Enables OFDMA with sub-channel allocation for efficient parallel communication.  

---

### Innovations  

1. **Custom User Inputs:**  
   - Allows users to specify custom configurations (number of users, conditions) for simulations in WiFi 4, WiFi 5, and WiFi 6.  

2. **Dynamic User Arrival (WiFi 5):**  
   - Simulates realistic conditions where not all users arrive at the same time.  

3. **WiFi 7 Implementation:**  
   - Adds simulation of the upcoming WiFi standard for comparison and experimentation.  

4. **Reusable Library:**  
   - Provides a library for loading project functions, enabling further usage and extension.  

---

## Steps to Run the Code  

1. Build the project using the command:  
    make  
    ./run  

**Note:** Took help from Internet and GenAI to generate code and Makefile.
