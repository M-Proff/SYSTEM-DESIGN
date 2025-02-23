#include <iostream>
#include <vector>
using namespace std;

// Vehicle class
class Vehicle {
private:
    string licensePlate;
    string vehicleType;

public:
    Vehicle(string plate, string type) : licensePlate(plate), vehicleType(type) {}

    string getLicensePlate() { return licensePlate; }
    string getVehicleType() { return vehicleType; }
};

// ParkingSpot class
class ParkingSpot {
private:
    int spotID;
    string spotType;
    bool isOccupied;
    Vehicle* assignedVehicle;

public:
    ParkingSpot(int id, string type) : spotID(id), spotType(type), isOccupied(false), assignedVehicle(nullptr) {}

    bool isSpotAvailable() { return !isOccupied; }

    bool assignVehicle(Vehicle* vehicle) {
        if (isOccupied) return false;
        assignedVehicle = vehicle;
        isOccupied = true;
        return true;
    }

    void removeVehicle() {
        assignedVehicle = nullptr;
        isOccupied = false;
    }

    string getSpotType() { return spotType; }
    int getSpotID() { return spotID; }
};

// ParkingLot class
class ParkingLot {
private:
    vector<ParkingSpot> spots;

public:
    ParkingLot(int numBike, int numCar, int numTruck) {
        int id = 1;
        for (int i = 0; i < numBike; i++) spots.push_back(ParkingSpot(id++, "Bike"));
        for (int i = 0; i < numCar; i++) spots.push_back(ParkingSpot(id++, "Car"));
        for (int i = 0; i < numTruck; i++) spots.push_back(ParkingSpot(id++, "Truck"));
    }

    bool parkVehicle(Vehicle* vehicle) {
        for (auto &spot : spots) {
            if (spot.getSpotType() == vehicle->getVehicleType() && spot.isSpotAvailable()) {
                if (spot.assignVehicle(vehicle)) {
                    cout << "Vehicle " << vehicle->getLicensePlate() << " parked at Spot " << spot.getSpotID() << endl;
                    return true;
                }
            }
        }
        cout << "No available spot for " << vehicle->getVehicleType() << endl;
        return false;
    }

    void removeVehicle(int spotID) {
        for (auto &spot : spots) {
            if (spot.getSpotID() == spotID) {
                spot.removeVehicle();
                cout << "Spot " << spotID << " is now free." << endl;
                return;
            }
        }
        cout << "Invalid Spot ID!" << endl;
    }

    void displayAvailableSpots() {
        int bikeCount = 0, carCount = 0, truckCount = 0;
        for (auto &spot : spots) {
            if (spot.isSpotAvailable()) {
                if (spot.getSpotType() == "Bike") bikeCount++;
                else if (spot.getSpotType() == "Car") carCount++;
                else if (spot.getSpotType() == "Truck") truckCount++;
            }
        }
        cout << "Available Spots -> Bike: " << bikeCount << ", Car: " << carCount << ", Truck: " << truckCount << endl;
    }
};

// Main function
int main() {
    // Create a parking lot with 2 Bike spots, 2 Car spots, and 1 Truck spot
    ParkingLot lot(2, 2, 1);

    // Create vehicles
    Vehicle bike1("B123", "Bike");
    Vehicle car1("C456", "Car");
    Vehicle truck1("T789", "Truck");
    Vehicle car2("C999", "Car");

    // Display available spots
    lot.displayAvailableSpots();

    // Park vehicles
    lot.parkVehicle(&bike1);
    lot.parkVehicle(&car1);
    lot.parkVehicle(&truck1);
    lot.parkVehicle(&car2);

    // Display updated availability
    lot.displayAvailableSpots();

    // Remove a parked vehicle
    lot.removeVehicle(2); // Assuming Spot 2 was occupied

    // Final availability check
    lot.displayAvailableSpots();

    return 0;
}
