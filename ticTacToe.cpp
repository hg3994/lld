/*
Requirements
============
1. It should be for a NxN board.
2. Player profile is required with features like name, email, phone, ranking, stats 
	(games played, won, lost, win%, etc)
3. Should be for only 2 players.

Classes To Think Of
===================
GameBoard, Player, etc.

Below is the implementation and perfectly working code: http://cpp.sh/8wacj

*/

#include <bits/stdc++.h>
using namespace std;


class Player {
private:
	string playerName;
	int playerId;
	// int ranking;
	char playerSymbol; // X or O

public:
	Player(string playerName, int playerId, char playerSymbol){
		this->playerName = playerName;
		this->playerId = playerId;
		this->playerSymbol = playerSymbol;
	}

	string getPlayerName(){
		return playerName;
	}

	char getPlayerSymbol(){
		return playerSymbol;
	}

};


class GameBoard {
private:
	vector<vector<char>> board;
	int boardSize;
	queue<Player*> nextTurn;

public:
	GameBoard(int boardSize, vector<Player*> players){
		this->boardSize = boardSize;
		this->board.resize(boardSize, vector<char>(boardSize,'.'));
		this->nextTurn.push(players[0]);
		this->nextTurn.push(players[1]);
	}

	void printGameBoard(){
		for(int i=0; i<boardSize; i++){
			for(int j=0; j<boardSize; j++){
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
	}

	bool validInput(int row, int col){
		if(row>=0 && row<boardSize && col>=0 && col<boardSize && board[row][col] == '.')
			return true;
		else
			return false;
	}

	int getUserInput(Player* p){
		int position;
		cout<<p->getPlayerName()<<", Enter a valid position from 1-"<<boardSize*boardSize<<endl;
		cin>>position;
		return position;
	}

	bool checkEndGame(Player* p, int row, int col){
		string winString;
		for(int i=0; i<boardSize; i++){
			winString += p->getPlayerSymbol();
		}
		string rowString, colString, diagonalString, reverseDiagonalString;

		for(int i=0; i<boardSize; i++){
			rowString += board[row][i];
			colString += board[i][col];
			if(row == col)
				diagonalString += board[i][i];
			if(row+col == boardSize-1)
				diagonalString += board[boardSize-1-i][i];
		}
		if(winString == rowString || winString == colString || winString == diagonalString || winString == reverseDiagonalString){
			printGameBoard();
			cout<<p->getPlayerName()<<" has won the game!"<<endl;
			return true;
		}
		return false;
	}

	void startGame(){
		int filled=0;
		while(true){
			if(filled == boardSize*boardSize){
				cout<<"Match Draw"<<endl;
				break;
			}
			printGameBoard();
			Player* p = nextTurn.front();
			nextTurn.pop();
			int position = getUserInput(p);

			int row = (position%boardSize == 0)? (position/boardSize)-1 : position/boardSize;
			int col = (position%boardSize == 0)? (boardSize-1) : (position%boardSize)-1;
			while(!validInput(row, col)){
				cout<<"Incorrect input. Please enter a valid position!"<<endl;
				int position = getUserInput(p);
				row = (position%boardSize == 0)? (position/boardSize)-1 : position/boardSize;
			    col = (position%boardSize == 0)? (boardSize-1) : (position%boardSize)-1;
			}
			board[row][col] = p->getPlayerSymbol();
			filled++;
			if(filled>=boardSize && checkEndGame(p, row, col))
				break;
			nextTurn.push(p);
		}
	}
};


int main(){
	Player* p1 = new Player("Alice", 1, 'X');
	Player* p2 = new Player("Bob",  2, 'O');

	vector<Player*> players = {p1, p2};
	GameBoard* gb = new GameBoard(2, players);
	gb->startGame();
	return 0;
}