#include <iostream>
#include <vector>
using namespace std;
 // ia hve changed somw code now in order to commit
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
    lot.parkVehicle(&bike1);  // difference between call by refernece and and without refernce
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
//minimum to make it work in interview

// #include <bits/stdc++.h>

// using namespace std;

// class Vehicle {
// private:
//     string plate;
//     string type;

// public:
//     Vehicle(string vehicle_plate, string vehicle_type) : plate(vehicle_plate), type(vehicle_type) {}

//     string display_plate() {
//         return plate;
//     }
//     string display_type() {
//         return type;
//     }
// };

// class ParkingSpot {
// private:
//     int park_number;
//     string park_type;
//     bool is_occupied;
//     Vehicle* veh_assigned;

// public:
//     ParkingSpot(int number, string type) : park_number(number), park_type(type), is_occupied(false), veh_assigned(NULL) {}

//     bool is_empty() {
//         return !is_occupied;
//     }

//     bool assign_vehicle(Vehicle* vehicle) {
//         if (is_occupied) return false;
//         is_occupied = true;
//         veh_assigned = vehicle;
//         return true;
//     }

//     string spot_type() {
//         return park_type;
//     }
// };

// class ParkingLot {
// private:
//     vector<ParkingSpot> spots;
//     int type_1, type_2;

// public:
//     ParkingLot(int cars, int bikes) : type_1(cars), type_2(bikes) {
//         int id = 1;
//         for (int i = 0; i < type_1; i++) spots.push_back(ParkingSpot(id++, "car"));
//         for (int i = 0; i < type_2; i++) spots.push_back(ParkingSpot(id++, "bike"));
//     }

//     void park_vehicle(Vehicle* vehicle) {
//         for (auto& spot : spots) { // Use reference to modify original object
//             if (spot.spot_type() == vehicle->display_type() && spot.is_empty()) {
//                 if (spot.assign_vehicle(vehicle)) {
//                     cout << "Vehicle with plate " << vehicle->display_plate() << " parked in a " << vehicle->display_type() << " spot.\n";
//                     return;
//                 }
//             }
//         }
//         cout << "No available spot for " << vehicle->display_type() << "\n";
//     }
// };

// int main() {
//     Vehicle bike_1("A123", "bike");
//     ParkingLot lot(0, 1);

//     lot.park_vehicle(&bike_1);
//     return 0;
// }

