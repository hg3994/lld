/*
Requirements
============
1. Elevator Car should move Up and Down
2. Buttons to control the elevator car
	a. Inside the Elevator Car on button Panel
	a. On the Floors of the Elevators
3. Dispatcher Unit Algorithm to control the Elevator Car - Brian of the Elevator
4. What to do when we have a lot of elevators?
	a. Some specific elevators work for some specific floors.
	b. Vreakdown elevators into multiple zones (1-20 floors -> e1-e4 | 21-40 -> e5-e8)
5. Door Open / Close
6. Limitations on Elevator Car

Classes To Think Of
===================
Elevator Car, Buttons, 

Below is the implementation and perfectly working code: http://cpp.sh/8wacj

*/


class ElevatorCar {
private:
	bool isMoving;
	bool isMovingUp;
	int currentFloor;
	int startFloor, endFloor; //zone of the elevator

	void moveToFloor(int floor){

	}
};


class ButtonPanel {
public:
	bool sendInstructionToDispatcher(int currentFloor, int destFloor, bool isMovingUp) = 0;
protected:
	int currentFloor;
	int destFloor;
	int isMovingUp;
}

class FloorButtonPanel : public ButtonPanel{
public:
	// isMovingUp - the button on the floor which is pressed (Up or Down)
	// NULL - we don't care where the elevator is right now
	// destFloor - the current Floor since we want the elevator to come here.
	bool sendInstructionToDispatcher(int currentFloor, int destFloor, bool isMovingUp) {
		sendInstruction(NULL, currentFloor, isMovingUp);
	}
}

class ElevatorCarButtonPanel : public ButtonPanel{
public:	
	bool sendInstructionToDispatcher(int currentFloor, int destFloor, bool isMovingUp) {
		// currentFloor - currentFloorOfCar
		// destFloor - DestinationFloor pressed in the elevator car
		// we can easily calc the isMovingUp or down on the basis of current and dest floor.
		sendInstruction(currentFloor, destFloor, isMovingUp);
	}
}


class Door {
	bool isOpen;

	bool closeDoor(){
	}

	bool openDoor(){
	}
}


class ElevatorSystem {
	vector<Elevator> elevators;
	vector<Floor> floors;

	startElevatorSystem(){
		// Initialize the system, set up zones, etc.
	}

	stopElevatorSystem(){
		// Stop a zone, all the elevators, etc.
	}

}

class Floor {
	int currentFloor;
	FloorButtonPanel floorButtonPanel;

	callElevator(int currentFloor, FloorButtonPanel floorButtonPanel){

	}

};


// FCFS
class Dispatcher {
	// If we are dealing with just 1 elevator
	// queue - As soon as we get a request from either FloorButtonPanel or ElevatorCarButtonPanel
	// we put the request in this queue and process it

	// For multiple elevators, it will get the zone and the elevators for them.
	// It will then get the current floor & currentDirection from the concerned elevators
	// On the basis of this, we select one elevator.
	// Eg: 	P1 at 1st floor pressed the UP button to go to 8th floor.
	//		P2 at 4th floor pressed DOWN to go to the 0th floor.
	//		There are two elevators e1, e2 which are at floor1, floor7
	//		e1 will be assigned to P1 since it is nearest and e2 will be called to 4th floor
	//		for P2 who wants to go to the 0th floor.
}

// Scan
class Dispatcher {
	// 
}

