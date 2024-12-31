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
