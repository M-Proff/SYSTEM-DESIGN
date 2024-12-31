#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constants
const string SPOT_COMPACT = "Compact";
const string SPOT_LARGE = "Large";
const string SPOT_MOTORBIKE = "Motorbike";
const string SPOT_ELECTRIC = "Electric";

const string VEHICLE_CAR = "Car";
const string VEHICLE_MOTORBIKE = "Motorbike";

const string VEHICLE_ELECTRIC = "Electric";
const string VEHICLE_TRUCK = "Truck";
const string VEHICLE_VAN = "Van";

class ParkingSpot {
private:
    string number;
    string type;
    bool free;

public:
    ParkingSpot(string number, string type) : number(number), type(type), free(true) {}

    bool isFree() { return free; }
    void assignVehicle() { free = false; }
    void removeVehicle() { free = true; }
    string getType() { return type; }
};

class Vehicle {
private:
    string licenseNumber;
    string type;

public:
    Vehicle(string license, string type) : licenseNumber(license), type(type) {}
    string getType() { return type; }
};

class ParkingFloor {
private:
    vector<ParkingSpot*> spots;

public:
    void addParkingSpot(ParkingSpot* spot) { spots.push_back(spot); }

    ParkingSpot* findFreeSpot(const string& type) {
        for (auto& spot : spots) {
            if (spot->isFree() && spot->getType() == type)
                return spot;
        }
        return nullptr;
    }
};

class ParkingLot {
private:
    vector<ParkingFloor*> floors;

public:
    void addFloor(ParkingFloor* floor) { floors.push_back(floor); }

    ParkingSpot* findFreeSpot(const string& vehicleType) {
        string spotType;
        if (vehicleType == VEHICLE_CAR) spotType = SPOT_COMPACT;
        else if (vehicleType == VEHICLE_MOTORBIKE) spotType = SPOT_MOTORBIKE;
        else if (vehicleType == VEHICLE_ELECTRIC) spotType = SPOT_ELECTRIC;
        else if (vehicleType == VEHICLE_TRUCK || vehicleType == VEHICLE_VAN) spotType = SPOT_LARGE;
        else return nullptr;

        for (auto& floor : floors) {
            ParkingSpot* spot = floor->findFreeSpot(spotType);
            if (spot) return spot;
        }
        return nullptr;
    }
};

int main() {
    ParkingLot lot;

    ParkingFloor* floor1 = new ParkingFloor();
    floor1->addParkingSpot(new ParkingSpot("1A", SPOT_COMPACT));
    floor1->addParkingSpot(new ParkingSpot("1B", SPOT_LARGE));
    lot.addFloor(floor1);

    Vehicle* car = new Vehicle("KA-01-HH-1234", VEHICLE_CAR);
    ParkingSpot* spot = lot.findFreeSpot(car->getType());

    if (spot) {
        cout << "Parking Spot Found" << endl;
        spot->assignVehicle();
    } else {
        cout << "No Parking Spot Available" << endl;
    }

    delete car;
    delete floor1;
    return 0;
}


// Constants
// Constants like SPOT_COMPACT, SPOT_LARGE, etc., represent the types of parking spots and vehicles as string literals. This avoids the use of enums and makes the code simpler for string-based comparisons.

// 1. ParkingSpot Class
// Represents an individual parking spot in the parking lot.

// Attributes:
// number: Identifier for the parking spot (e.g., "1A").
// type: Type of the spot (e.g., "Compact", "Large").
// free: A boolean indicating whether the spot is free or occupied.
// Methods:
// isFree(): Checks if the spot is available.
// assignVehicle(): Marks the spot as occupied.
// removeVehicle(): Marks the spot as free.
// getType(): Returns the type of the parking spot.
// Purpose:
// This class encapsulates the state and behavior of a parking spot, ensuring proper encapsulation.

// 2. Vehicle Class
// Represents a vehicle that needs parking.

// Attributes:
// licenseNumber: The license plate of the vehicle (e.g., "KA-01-HH-1234").
// type: The type of vehicle (e.g., "Car", "Motorbike").
// Methods:
// getType(): Returns the type of the vehicle.
// Purpose:
// This class models vehicles that will be assigned parking spots, ensuring each vehicle has a unique license and type.

// 3. ParkingFloor Class
// Represents a single floor in the parking lot, containing multiple parking spots.

// Attributes:
// spots: A vector of pointers to ParkingSpot objects.
// Methods:
// addParkingSpot(ParkingSpot* spot): Adds a parking spot to the floor.
// findFreeSpot(const string& type): Finds the first free spot of the specified type on the floor. Returns a pointer to the spot or nullptr if no spot is available.
// Purpose:
// This class organizes parking spots on a specific floor and provides functionality to find available spots efficiently.

// 4. ParkingLot Class
// Represents the entire parking lot, consisting of multiple floors.

// Attributes:
// floors: A vector of pointers to ParkingFloor objects.
// Methods:
// addFloor(ParkingFloor* floor): Adds a floor to the parking lot.
// findFreeSpot(const string& vehicleType): Finds the first free parking spot for a given vehicle type across all floors. Matches the vehicle type to the appropriate spot type.
// Purpose:
// This class manages the overall parking lot, coordinates between floors, and assigns spots to vehicles based on their type.

// 5. Main Function
// Simulates the operation of the parking lot.

// Steps:
// Create a ParkingLot object: Represents the entire parking system.
// Add a ParkingFloor: A floor is created and parking spots are added to it.
// Create a Vehicle: A vehicle is instantiated with its license number and type.
// Find and Assign a Parking Spot:
// The parking lot searches for an available spot that matches the vehicle's type.
// If a spot is found, it is marked as occupied; otherwise, a message is displayed indicating no availability.
// How the Code Adheres to SOLID Principles
// Single Responsibility Principle (SRP):

// Each class has a single, well-defined responsibility:
// ParkingSpot: Manages parking spot behavior.
// Vehicle: Represents vehicles.
// ParkingFloor: Organizes spots on a floor.
// ParkingLot: Coordinates the parking system.
// Open/Closed Principle (OCP):

// The code can be extended (e.g., new spot or vehicle types) without modifying existing classes.
// Liskov Substitution Principle (LSP):

// Not directly applicable here as there is no inheritance hierarchy.
// Interface Segregation Principle (ISP):

// Each class has a minimal set of methods relevant to its role.
// Dependency Inversion Principle (DIP):

// Higher-level classes (ParkingLot) depend on abstractions (like ParkingFloor), not concrete implementations.
// Summary
// The code models a simple parking lot system where:

// Vehicles are assigned parking spots based on their type.
// Parking floors manage the allocation of spots.
// The parking lot oversees the entire process, ensuring efficient spot assignment.
// This modular design ensures clarity, maintainability, and extensibility.