/*
Requirements
============
1. There should be multiple floors in a parking lot.
2. There should be multiple gates in the parking lot.
3. The entry gate should process parking ticket.
4. The exit gates should process the payment on an hourly basis.
5. Parking facility for different types of vehicles.
6. There should be display boards at each floor showing 
	the detail of vacant spots on the floor.

Classes To Think Of
===================
Parking Lot, Floors, Parking Space, Gates, Ticket Processing, Vehicles, Display Boards

*/


class ParkingLot {

	vector<ParkingFloor> parkingFloors;
	vector<Enterance> enterances;
	vector<Exit> exit;

	Address address;
	string parkingLotName;

	bool isParkingSpaceAvailableForVehicle(Vehicle vehicle);

};


class ParkingFloor {
	int levelId;
	bool isFull;
	vector<ParkingSpace> parkingSpaces;

	ParkingDisplayBoard parkingDisplayBoard;
};


class Gate {
	int gateId;
	ParkingAttendant parkingAttendant;
};

class Enterance : public Gate {

	ParkingTicket getParkingTicket(Vehicle vehicle);
};

class Exit : public Gate {

	ParkingTicket payForParkingPayment(ParkingTicket parkingTicket, PaymentType paymentType);
};


class Address {
	string country, state, city, street, pinCode;
};

class ParkingSpace {
	int spaceId;
	bool isFree;
	double costPerHour;
	Vehicle vehicle;
	ParkingSpaceType parkingSpaceType;

};


class ParkingDisplayBoard {

	unordered_map <ParkingSpaceType, Integer> freeSpotsAvailableMap;

	void updateFreeSpotsAvailable(ParkingSpaceType parkingSpaceType, int spaces);
};

class Account {
	string name, email, password. empId, Address address;
};

class Admin : public account {
	bool addParkingFloor (ParkingLot parkinglot, ParkingFloor parkingFloor);
	bool addParkingSpace (ParkingSpace parkingSpace, ParkingFloor parkingFloor);
	bool addParkingDisplayBoard (ParkingDisplayBoard parkingDisplayBoard, ParkingFloor parkingFloor);
};

class ParkingAttendant : public Account {
	Payment paymentService;
	bool processVehicleEntry(Vehicle vehicle);
	PaymentInfo processPayment(ParkingTicket parkingTicket, paymentType paymentType);
};


class Vehicle {
	string licenseNumber;
	VehicleTyoe vehicleType;
	PakingTicket parkingTicket;
	PaymentInfo paymentInfo;
};

class ParkingTicket {
	int ticketId;
	int levelId;
	int spaceId;
	Date vehicleEntryDateTime;
	Date vehicleExitDateTime;
	parkingSpaceType parkingSpaceType;
	double totalCost;
	ParkingTicketStatus ParkingTicketStatus;

	void updateTotalCost();
	void updateVehicleExitTime(Date vehicleExitDateTime);
};


class Payment {
	PaymentInfo makePayment(ParkingTicket parkingTicket, ParkingType paymentType);
};

class PaymentInfo {
	double amount;
	Date paymentDate;
	int transactionId;
	parkingTicket parkingTicket;
	paymentStatys paymentStatus;
};

enum class PaymentType { Cash = 0, CreditCard = 1, DebitCard = 2, UPI = 3 };
enum class ParkingSpaceType { BikeParking, CarParking, TruckParking }; // Automatically init from 0...
enum class VehicleType { Bike, Car, Truck };
enum class ParkingTicketStatus { Paid, Active };
enum class PaymentStatus { Unpaid, Pending, Completed, Declined, Cancelled, Refunded };


