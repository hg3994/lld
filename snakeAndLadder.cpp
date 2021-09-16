/*
Requirements
============
1. It should be a multiplayer game.
2. Customizable Board in terms of snake and ladder placement & board size.
3. Customizable in terms of number of dice used
4. When Game Board loads it should:
	a. Load the configured Board size.
	b. Load the configured Snake and Ladder positions.
	c. Load the configured Number of dice
	d. Load the number of players who will play the game and all of them start at 0.


Classes To Think Of
===================
Configuration, Snake, Ladder, GameBoard, Player.

Below is the implementation and perfectly working code: https://ideone.com/M5yHh9

*/

#include <bits/stdc++.h>
using namespace std;


class Player {
private:
	string playerName;
	int id;

public:
	Player(string playerName, int id){
		this->playerName = playerName;
		this->id = id;
	}
	
	string getPlayerName(){
		return playerName;
	}
};


class Dice {
private:
	int numberOfDice;

public:

	Dice () {}
	Dice(int numberOfDice){
		this->numberOfDice = numberOfDice;
	}

	int rollDice() {
		return (random()%((numberOfDice*6 - numberOfDice*1)+1)) + numberOfDice;
	}
};


class Jumper {
private:
	int startPoint;
	int endPoint;
public:
	Jumper(int startPoint, int endPoint){
		this->startPoint = startPoint;
		this->endPoint = endPoint;
	}
	
	int getStartPoint(){
		return startPoint;
	}
	
	int getEndPoint(){
		return endPoint;
	}
};


class GameBoard {
private:
	Dice* dice;
	queue<Player*> nextTurn;
	vector<Jumper*> snakes;
	vector<Jumper*> ladder;
	unordered_map<string, int> playersCurrentPosition;
	int boardSize;
public:
	GameBoard(Dice* dice, queue<Player*> nextTurn, vector<Jumper*> snakes, vector<Jumper*> ladder, unordered_map<string, int> playersCurrentPosition, int boardSize){
		this->dice = dice;
		this->nextTurn = nextTurn;
		this->snakes = snakes;
		this->snakes = snakes;
		this->ladder = ladder;
		this->playersCurrentPosition = playersCurrentPosition;
		this->boardSize = boardSize;
	}

	// This function can be refactored into several other functions
	void StartGame(){
		while(nextTurn.size() > 1){
			Player* player = nextTurn.front();
			nextTurn.pop();

			int currentPosition = playersCurrentPosition[player->getPlayerName()];
			int diceValue = dice->rollDice();
			cout<<player->getPlayerName()<<" rolled the dice and got "<<diceValue<<endl;
			int nextCell = currentPosition + diceValue;
			if(nextCell > boardSize)
				nextTurn.push(player);
			else if (nextCell == boardSize)
				cout<<player->getPlayerName()<<" has won the game!"<<endl;
			else {
				bool change = false;
				for(auto &s: snakes){
					if(s->getStartPoint() == nextCell){
						nextCell = s->getEndPoint();
						change = true;
						cout<<player->getPlayerName()<<" got bitten by snake!"<<endl;
					}
				}
				
				for(auto &s: ladder){
					if(s->getStartPoint() == nextCell){
						nextCell = s->getEndPoint();
						change = true;
						cout<<player->getPlayerName()<<" got a ladder!"<<endl;
					}
				}

				if(nextCell == boardSize)
					cout<<player->getPlayerName()<<" has won the game!"<<endl;
				else {
					playersCurrentPosition[player->getPlayerName()] = nextCell;
					cout<<player->getPlayerName()<<" is at position "<<nextCell<<endl;
					nextTurn.push(player);
				}
			}
		}
	}
};


int main(){

	Dice* dice = new Dice(1);
	Player* p1 = new Player("Harshit", 1);
	Player* p2 = new Player("Vijaya", 2);
	queue<Player*> allPlayers;
	allPlayers.push(p1);
	allPlayers.push(p2);
	Jumper* snake1 = new Jumper(10, 2);
	Jumper* snake2 = new Jumper(99, 12);
	vector<Jumper*> snakes = {snake1, snake2};
	Jumper* ladder1 = new Jumper(2, 25);
	Jumper* ladder2 = new Jumper(40, 89);
	vector<Jumper*> ladders = {ladder1, ladder2};
	unordered_map<string, int> playersCurrentPosition;
	playersCurrentPosition[p1->getPlayerName()] = 0;
	playersCurrentPosition[p2->getPlayerName()] = 0;
	GameBoard* gb = new GameBoard(dice, allPlayers, snakes, ladders, playersCurrentPosition, 100);
	gb->StartGame();
	return 0;
}