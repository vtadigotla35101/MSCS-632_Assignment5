#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// --- 1. Ride Base Class ---
class Ride {
protected:
    std::string rideID;
    std::string pickupLocation;
    std::string dropoffLocation;
    double distance;

public:
    Ride(std::string id, std::string pickup, std::string dropoff, double dist)
        : rideID(id), pickupLocation(pickup), dropoffLocation(dropoff), distance(dist) {}

    // Virtual destructor is crucial for polymorphism to clean up derived classes
    virtual ~Ride() {}

    // Virtual method for Polymorphism
    virtual double calculateFare() const {
        return distance * 1.50; // Base rate
    }

    virtual void rideDetails() const {
        std::cout << "[ID: " << rideID << "] From: " << pickupLocation 
                  << " To: " << dropoffLocation << " (" << distance << " miles)";
    }
};

// --- 2. Specific Ride Subclasses ---
class StandardRide : public Ride {
public:
    StandardRide(std::string id, std::string p, std::string d, double dist) 
        : Ride(id, p, d, dist) {}

    double calculateFare() const override {
        return distance * 1.25; // Standard rate
    }

    void rideDetails() const override {
        std::cout << "Standard Ride ";
        Ride::rideDetails();
    }
};

class PremiumRide : public Ride {
public:
    PremiumRide(std::string id, std::string p, std::string d, double dist) 
        : Ride(id, p, d, dist) {}

    double calculateFare() const override {
        return (distance * 2.50) + 5.00; // Premium rate + booking fee
    }

    void rideDetails() const override {
        std::cout << "Premium Ride  ";
        Ride::rideDetails();
    }
};

// --- 3. Driver Class (Encapsulation) ---
class Driver {
private:
    std::string driverID;
    std::string name;
    double rating;
    std::vector<Ride*> assignedRides; // Private collection

public:
    Driver(std::string id, std::string n, double r) : driverID(id), name(n), rating(r) {}

    void addRide(Ride* ride) {
        assignedRides.push_back(ride);
    }

    void getDriverInfo() const {
        std::cout << "\n=== Driver Profile ===" << std::endl;
        std::cout << "Name: " << name << " | Rating: " << rating << "/5.0" << std::endl;
        std::cout << "Completed Rides:" << std::endl;
        for (const auto& ride : assignedRides) {
            ride->rideDetails();
            std::cout << " | Fare: $" << std::fixed << std::setprecision(2) 
                      << ride->calculateFare() << std::endl;
        }
    }
};

// --- 4. Rider Class ---
class Rider {
private:
    std::string riderID;
    std::string name;
    std::vector<Ride*> requestedRides;

public:
    Rider(std::string id, std::string n) : riderID(id), name(n) {}

    void requestRide(Ride* ride) {
        requestedRides.push_back(ride);
    }

    void viewRides() const {
        std::cout << "\n=== Rider History: " << name << " ===" << std::endl;
        for (const auto& ride : requestedRides) {
            ride->rideDetails();
            std::cout << std::endl;
        }
    }
};

// --- 5. Main Function (System Functionality) ---
int main() {
    // Instantiate Driver and Rider
    Driver* myDriver = new Driver("D001", "Tadigotla", 4.9);
    Rider* myRider = new Rider("R99", "Vishnu");

    // 5. Demonstrate Polymorphism by storing different types in a list
    std::vector<Ride*> systemRides;
    
    systemRides.push_back(new StandardRide("Trip-STD", "Cinemark", "AMC", 15.2));
    systemRides.push_back(new PremiumRide("Trip-PRE", "Chipotle", "Chick-Fil-A", 5.5));
    systemRides.push_back(new StandardRide("Trip-STD2", "T-Mobile", "Verizon", 8.0));

    // Assigning rides to driver and rider
    for (Ride* r : systemRides) {
        myDriver->addRide(r);
        myRider->requestRide(r);
    }

    // Display Information
    myRider->viewRides();
    myDriver->getDriverInfo();

    // Memory Cleanup (SRE/DevOps best practice)
    for (Ride* r : systemRides) {
        delete r;
    }
    delete myDriver;
    delete myRider;

    return 0;
}