#pragma once

#include <iostream>

using namespace std;

class Board;

class BoardField {
private:
	char color; // W lub B lub '-' lub '+'
	char first_coordinate;
	int second_coordinate;
	int x;
	int y;
	Board* board;
public:
	BoardField();
	void setFirstCoordinate(char first);
	void setSecondCoordinate(int second);
	void setColor(char col);
	char getFirstCoordinate() const;
	int getSecondCoordinate() const;
	char getColor() const;
	int getX() const;
	int getY() const;

	void setBoard(Board* b);
	void setX(int x);
	void setY(int y);
	
	bool checkIfRowFull(int x_direction, int y_direction);

	bool moveLeft(char colorOfWhoPushes, bool ifPrintMoveInfo);
	bool moveRight(char colorOfWhoPushes, bool ifPrintMoveInfo);
	bool moveUpLeft(char colorOfWhoPushes, bool ifPrintMoveInfo);
	bool moveUpRight(char colorOfWhoPushes, bool ifPrintMoveInfo);
	bool moveDownLeft(char colorOfWhoPushes, bool ifPrintMoveInfo);
	bool moveDownRight(char colorOfWhoPushes, bool ifPrintMoveInfo);

};