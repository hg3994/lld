/*
Requirements
============
1. There should be multiple floors in a parking lot.
2. There should be multiple categories of parking space (for different types of vehicles).
3. It should allow multiple entry and exit points.
4. Should not allow more vehicles than allocated space for each category.
5. Charge on an hourly basis.
6. Display available number of parking space for each category on entry itself.

Classes To Think Of
===================
Parking Lot -> Floors -> Parking Space, Gates, Ticket Processing, Vehicles, Display Boards

HLD
===

								|----->Payment Service---------------\
								|									  \
USER---->Ticket Allocation Service--------------------------------------> Database
								|									 /
								|-----> Space Allocation Service----/

1. User goes to counter at entry gate to collect the ticket
2. Guy at counter checks for space allocation and enter details like vehicle number, entry time, type, etc. and then create a ticket.
3. User gives a ticket at exit gate and ticket allocation service will make a call to payment service & calculate the charge
4. All the details will be saved in the database.

*/


#include <bits/stdc++.h>
using namespace std;


// Singleton Class.
class ParkingLot {
private:
	static ParkingLot *instance;
	string parkingLotName;
	string address;
	vector<ParkingFloor> parkingFloors;
	// Private constructor so no objects can be created.
	ParkingLot(string parkingLotName, string address, vector<ParkingFloor> parkingFloors){
		this->parkingLotName = parkingLotName;
		this->address = address;
		this->parkingFloors = parkingFloors;
	}
	
public:

	static ParkingLot* getInstance(string parkingLotName, string address, vector<ParkingFloor> parkingFloors){
		if (!instance)
        	instance = new ParkingLot(parkingLotName, address, parkingFloors);
        return instance;
	}

	void addFloor(string name, unordered_map<ParkingSlotType, unordered_map <string, ParkingSlot> > parkingSlots){
		ParkingFloor pf = new ParkingFloor(name, parkingSlots);
		parkingFloors.push_back(pf);
	}

	void removeFloor(){
		// TODO
	}

	Ticket assignTicket(Vehicle vehicle){
		ParkingSlot parkingSlot = getParkingSlotForVehicleAndPark(vehicle);
		if(parkingSlot == NULL)
			return NULL;
		Ticket parkingTicket = createTicketForSlot(parkingSlot, vehicle);
		// TODO the ticket class...
	}

	double scanAndPay(Ticket ticket){
		// TODO
	}


private:
	ParkingSlot getParkingSlotForVehicleAndPark(Vehicle vehicle){
		ParkingSlot ps = NULL;
		for(auto floor: parkingFloors){
			ps = floor.getRelevantSlotForVehicleAndPark(vehicle);
			if(ps != NULL)
				break;
		}
		return ps;
	}

};






class ParkingFloor {
private:
	string name;
	// {TwoWheeler: {'T1': T1's ParkingSlot }}
	unordered_map<ParkingSlotType, unordered_map <string, ParkingSlot> > parkingSlots;

public:
	ParkingFloor(string name, unordered_map<ParkingSlotType, unordered_map <string, ParkingSlot> > parkingSlots){
		this->name = name;
		this->parkingSlots = parkingSlots;
	}


	ParkingSlot getRelevantSlotForVehicleAndPark(Vehicle vehicle){
		VehicleCategory vc = vehicle.getVehicleCategory();
		ParkingSlotType pst = pickCorrectSlot(vc);
		unordered_map <string, ParkingSlot> ps = parkingSlots[pst];
		ParkingSlot slot = NULL;
		for(auto m: ps){
			if(m.second.isAvailable()){
				slot = m.second;
				slot.addVehicle(vehicle);
				break;
			}
		}
		return slot;
	}

private:
	ParkingSlotType pickCorrectSlot(VehicleCategory vc){
		if(vc == ParkingSlotType::TwoWheeler) return ParkingSlotType::TwoWheeler;
		else if(vc == ParkingSlotType::HatchBack || vc == ParkingSlotType::Sedan) return ParkingSlotType::Compact;
		else if(vc == ParkingSlotType::SUV) return ParkingSlotType::Medium;
		else if(vc == ParkingSlotType::Bus) return ParkingSlotType::Large;
		return NULL;
	}


	// This should not be here...
	double getPriceForParking(long duration, ParkingSlot ps){
		if (ps == TwoWheeler)
			return duration*1;
		else if(ps == Compact)
			return duration*1;
		else if(ps == Medium)
			return duration*1;
		else if(ps == Large)
			return duration*1;
	}

};

enum class ParkingSlotType { 
	TwoWheeler, Compact, Medium, Large
};

// Actual slot where the parking will happen
class ParkingSlot {
	string name;
	bool isAvailable = true;
	Vehicle vehicle;
	// ParkingSlotType parkingSlotType;
public:
	ParkingSlot(string name) {
		this->name = name;
	}

	void addVehicle(Vehicle vehicle){
		this->vehicle = vehicle;
		this->isAvailable = false;
	}

	void removeVehicle(Vehicle vehicle){
		this->vehicle = NULL;
		this->isAvailable = true;
	}

};

class Vehicle {
	string vehicleNumber;
	VehicleCategory vehicleCategory;
public:
	getVehicleCategory(){
		return vehicleCategory;
	};
};

enum class VehicleCategory { 
	TwoWheeler, HatchBack, Sedan, SUV, Bus
};





// Singleton Class Instance
ParkingLot *ParkingLot::instance = 0;
int main() {
	ParkingLot *s = s->getInstance("abc", "123");
	return 0;
}