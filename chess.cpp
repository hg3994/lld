/*
Requirements
============
1. Everything in Chess: The Board, The pieces, The Moves, everything!

Classes To Think Of
===================
ChessBoard, Pieces, player

*/

class Chess {
	ChessBoard chessBoard;
	vector<Player> players;
	Player currentPlayer;
	vector<Move> movesList;
	GameStatus gameStatus;

	bool playerMove(CellPosition fromPosition, CellPosition toPosition, Piece piece);
	bool endGame();
private:
	void changeTurn(); // This need not be called from outside the system. It will be called from playermove.
};


class Player {
	Account account;
	Color color;
	Time timeLeft;
};

class Account {
	string username, password, name, email, phone;
};

class Time {
	int mins, secs;
};

enum class COlor { Black, White };
enum GameStatus { Active, Paused, Fortgeight, BlackWon, WhiteWon };

class ChessBoard {
	vector<vector<Cell>> board;

	void resetBoard();
	void updateBoard(Move move); // called from playerMove
};

class Cell {
	Color color;
	Piece piece;
	CellPosition position;
};

class CellPosition {
	char ch;
	int i;
};

class Move {
	Player turn;
	Piece piece;
	Piece KilledPiece;
	CellPosition startPosition;
	CellPosition endPosition;
};

// This is an Abstract Class since it has pure virtual functions which will be implmented in the Derived Class.
// Can not initialize a Piece object
class Piece { 
	Color color;
	PieceStatus status;

public:
	virtual bool move(CellPosition fromPosition, CellPosition toPosition) = 0;
	virtual vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition) = 0;
};

enum class PieceStatus { Alive, Dead };

class Pawn : public Piece {

	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};

class Knight : public Piece {
	
	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};

class Bishop : public Piece {
	
	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};

class Rook : public Piece {
	
	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};

class King : public Piece {
	
	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};

class Queen : public Piece {
	
	bool move(CellPosition fromPosition, CellPosition toPosition);
	vector<CellPosition> possibleMoves(CellPosition fromPosition, CellPosition toPosition);
};