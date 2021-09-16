/*
Food ordering system
====================

Description: 
	Implement an online food ordering system. 

Features: 
	1. This system has a tie-up with restaurants where each restaurant has a menu with all the 
	items & their prices. Restaurants also have a rating out of 5. 
	2. Each restaurant has max #orders it can process at any given time. Beyond that, it 
	shouldn’t be assigned any further orders until an ongoing order is completed. 
	3. Once an order is ACCEPTED, the restaurant can mark it as COMPLETED when the order is ready. This will free up the processing capacity of the restaurant. A restaurant can’t CANCEL an ACCEPTED order. 
	4. An order will be auto-assigned to a restaurant based on a selection strategy. Eg: Assign 
	by lowest cost or best rating. 
	5. An order will be auto-assigned to a restaurant only if all the items in an order can be fulfilled by a single restaurant. Else the order will not be ACCEPTED. 


Requirement: 
	Onboard a new restaurant with a menu.
	A customer should be able to place an order by giving items, respective quantities & selection strategy.
	Restaurants can mark ACCEPTED orders as COMPLETED. Orders once ACCEPTED can’t be CANCELLED by a restaurant.
	Order will be auto-assigned to a restaurant based on a selection strategy. 
	Implement at least one restaurant selection strategy. 
	A restaurant should be able to update its menu. For simplicity, a restaurant can't delete an item from the menu.
	Note: Do not use any database or NoSQL store, use an in-memory store. 

Expectation: 
	1. Make sure that you have working and demoable & functionally correct code. 
	2. Use proper abstractions, separation of concerns, proper entity modeling 
	3. Use appropriate design patterns wherever required.
	4. The code should be modular, extensible, readable and unit-testable. 
	5. Proper exception handling is required. 
	6. Restaurant selection strategy must be pluggable 
	7. Concurrency handling (BONUS / Good to have) 
	8. Unit test cases (Bonus/ Good to have)

Sample test cases: 

	This is for illustration purposes only.
	You can define your ways to take input.
	You can use driver class or take input from console or you can write UT’s
	
	1. Onboard Restaurants 
		R1  “max_orders_that_can_be_processed_at_a_time” : 5, “Menu”: [Veg Biryani : Rs.100, Chicken Biryani: Rs.150], 
		“rating”: 4.5/5 

		R2 “max_orders_that_can_be_processed_at_a_time”: 5, 
		menu: [Chicken Biryani : Rs.175, Idli : Rs.10, Dosa : Rs.50, Veg Biryani : Rs. 80], 
		rating: 4/5 

		R3 “max_orders_that_can_be_processed_at_a_time”: 1, 
		menu: [Gobi Manchurian : Rs.150, Idli : Rs.15, Chicken Biryani : Rs.175, Dosa: Rs.30 ], 
		rating: 4.9/5 

	2. Update restaurant menu 

		ADD: {Restaurant_1, add, Chicken65, Rs.250} 
		UPDATE: {Restaurant_2, update, Chicken Biryani, Rs.150}

	3. Place Order 

		Order1:
			Input: { user: Ashwin, items: [ 3*Idli, 1*Dosa ], selection: Lowest cost } 
			Output: Order assigned to R3 

		Order2:
			Input: { user: Harish, items: [ 3*Idli, 1*Dosa ], selection: Lowest cost } 
			Output: Order assigned to R2 (Not R3 since it has reached its full capacity from Order1) 

		Order3: 
			Input: { user: Shruthi, items: [3*Veg Biryani], selection: ‘Highest rating’ } 
			Output: Order assigned to R1 

	4. Update Order Status: 
		R3 marks Order1 as COMPLETED Order4: 
		Input: { user: Harish, items: [ 3*Idli, 1*Dosa ], selection: Lowest cost } 
		      Output: Order assigned to R3 (since R3 has COMPLETED Order1) 

	5. Order4: 
		Input: {user: xyz, items: [1*Paneer Tikka, 1*Idli], selection: ‘Lowest cost} 
		Output: Order can’t be fulfilled (since none of the restaurants above serve Paneer Tikka) 

ScratchPad:

	Classes:
	Restaurant, 
		rating
		name
		max_orders
		addingfood()
		updateFood()

	Food, 
		name
		price

	User
		name

	Order
		orderId
		selectionStrategy - lowCost, highestRating
		items-> Food.

Company:
	Flipkart

https://ideone.com/btyvgn

*/

#include <bits/stdc++.h>
using namespace std;


class Food {
public:
    string name;
	int price; 
	Food(){}
	Food(string name, int price){
		this->name = name;
		this->price = price;
	}
};

class User {
private:
	string name;
	int userId;
public:
	User(){}
	User(string name, int userId){
		this->name = name;
		this->userId = userId;
	}
};


// Abstract Class
// class SelectionStratergy {
// public:
// 	Restaurant selectRestaurantWithStrategy() = 0;
// };

// class lowCost : public SelectionStratergy{
// 	selectRestaurantWithStrategy() {

// 	}
// };

// class highestRating : public SelectionStratergy {
// 	selectRestaurantWithStrategy() {
		
// 	}
// };


class Restaurant {
private:
	string name;
	float rating;
	int maxOrders;
	int currentOrders;
	vector<Food*> menu;

public:
    Restaurant(){}
	Restaurant(string name, float rating, int maxOrders, vector<Food*> menu){
		this->name = name;
		this->rating = rating;
		this->maxOrders = maxOrders;
		this->currentOrders = 0;
		this->menu = menu;
	}

	void addFoodInMenu(Food* newFood){
		menu.push_back(newFood);
	}

	bool updateFoodInMenu(Food* updatedFood){
		bool isUpdated = false;
		for(auto& f: menu){
			if(f->name == updatedFood->name){
				f->price = updatedFood->price;
				isUpdated = true;
				break;
			}
		}
		return isUpdated;
	}
	
	void printMenu(){
		for(auto& f: menu){
			cout<<f->name<<" -> "<<f->price<<endl;
		}
	}
	
	int getCurrentOrders(){
		return this->currentOrders;
	}
	
	int getMaxOrders(){
		return this->maxOrders;
	}
	
	string getName(){
		return this->name;
	}
	
	vector<Food*> getMenu(){
		return this->menu;
	}
	
	bool decreaseCurrentOrderOfRestaurantBy1(){
		if(this->currentOrders > 0){
			this->currentOrders--;
			return true;
		}
		else {
			return false;
		}
	}

};

class Order {
private:
	string orderId;
	string status;
	Restaurant* restaurant;
	vector<Food*> orderItems;
	User* orderUser;
	string orderSelectionStratergy;
public:
	Order() {}
	Order(string orderId, vector<Food*> orderItems, User* orderUser, string orderSelectionStratergy){
		this->orderId = orderId;
		this->status = "ACCEPTED";
		this->orderItems = orderItems;
		this->orderUser = orderUser;
		this->orderSelectionStratergy = orderSelectionStratergy;
	}
	
	bool markOrderCompleted(Order* order){
		if(order->status ==  "ACCEPTED"){
			order->status = "COMPLETED";
			Restaurant* rest = order->restaurant;
			rest->decreaseCurrentOrderOfRestaurantBy1();
			return true;
		}
		else {
			// Something is wrong, or already accepted.
			return false;
		}
	}
	
	Restaurant* assignRestaurantToOrder(vector<Restaurant*> allRestaurants){
		// 1. Check and return all Restaurants that have all orderedItems
		// 2. Check and return all that have aviailibility for processing the order
		vector<Restaurant*> restaurantsHavingOrders = restaurantsThatHaveAllOrderedItems(allRestaurants);
		
		// 3. assignTheRestaurant on the basis of Strategy
		return restaurantsHavingOrders[0];
	}
	
	vector<Restaurant*> restaurantsThatHaveAllOrderedItems(vector<Restaurant*> allRestaurants){
		vector<Restaurant*> selectedRestaurants;
		for(auto& r: allRestaurants){
			bool canFullfillOrder = checkIfRestaurantHasAllOrderedItems(r->getMenu());
			if(canFullfillOrder && r->getMaxOrders() != r->getCurrentOrders()){
				// cout<<"Restaurant selected: "<<r->getName()<<endl;
				selectedRestaurants.push_back(r);
			}
				
		}
		return selectedRestaurants;
	}
	
	bool checkIfRestaurantHasAllOrderedItems(vector<Food*> menu){
		int sizeOfOrder = (this->orderItems).size();
		int currentSize=0;
		for(auto&item: this->orderItems){
			for(auto& f: menu){
				if(f==item){
					currentSize++;
					break;
				}
			}
		}
		return currentSize==sizeOfOrder;
	}
};






int main() {
	User* user1 = new User("Harshit", 1);
	Food* food1 = new Food("Veg Biryani", 100);
	Food* food2 = new Food("Chicken Biryani", 150);
	Food* food3 = new Food("Kaju Biryani", 150);
	
	vector<Food*> items= {food1, food2};
	vector<Food*> items2= {food1};
	
	Order* o1 = new Order("1", items, user1, "lowCost");
	
	Restaurant* r1 = new Restaurant ("Paradise", 4.5, 5, items);
	Restaurant* r2 = new Restaurant ("Veggie Paradise", 5, 2, items2);
	
	vector<Restaurant*> allRestaurants = {r1, r2};
	Restaurant* r = o1->assignRestaurantToOrder(allRestaurants);
	cout<<r->getName()<<endl;
	
	r1->addFoodInMenu(food3);
	r1->printMenu();
	Food* food4 = new Food("Kaju Bryani", 200);
	r1->updateFoodInMenu(food4);
	cout<<"-------"<<endl;
	r1->printMenu();
	return 0;
}