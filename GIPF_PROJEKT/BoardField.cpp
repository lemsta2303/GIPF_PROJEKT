#include <iostream>

#include "BoardField.h"
#include "Board.h"

using namespace std;

BoardField::BoardField() {
	color = '-';
	first_coordinate = 'x';
	second_coordinate = -1;
	x = -1;
	y = -1;
}

void BoardField::setFirstCoordinate(char first) {
	first_coordinate = first;
}

void BoardField::setSecondCoordinate(int second) {
	second_coordinate = second;
}

void BoardField::setColor(char col) {
	color = col;
}

char BoardField::getFirstCoordinate() const {
	return first_coordinate;
}

int BoardField::getSecondCoordinate() const {
	return second_coordinate;
}

char BoardField::getColor() const {
	return color;
}

int BoardField::getX() const {
	return x;
}

int BoardField::getY() const {
	return y;
}

void BoardField::setBoard(Board *b) {
	board = b;
}

void BoardField::setX(int x) {
	this->x = x;
}

void BoardField::setY(int y) {
	this->y = y;
}

bool BoardField::checkIfRowFull(int x_direction, int y_direction) {
	int x = this->x;
	int y = this->y;
	for (int i = 0; i < board->getBoardSize()+1; i ++ ) {
		x += x_direction;
		y += y_direction;
		if (board->getBoardFieldAtXY(x, y)->getColor() == '_') return false;
	}
	return true;
}

void BoardField::moveLeft(char colorOfWhoPushes) {
	if (!checkIfRowFull(0,-2)) {
		board->getBoardFieldAtXY(x, y - 2)->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
}

void BoardField::moveRight(char colorOfWhoPushes) {
	if (!checkIfRowFull(0,2)) {
		board->getBoardFieldAtXY(x, y + 2)->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
}

void BoardField::moveUpLeft(char colorOfWhoPushes) {
	if (!checkIfRowFull(1, -1)) {
		board->getBoardFieldAtXY(x+1 , y-1 )->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
	
}

void BoardField::moveUpRight(char colorOfWhoPushes) {
	if (!checkIfRowFull(1, 1)) {
		board->getBoardFieldAtXY(x + 1, y+1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
}

void BoardField::moveDownLeft(char colorOfWhoPushes) {
	if (!checkIfRowFull(-1, -1)) {
		board->getBoardFieldAtXY(x - 1, y-1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
}

void BoardField::moveDownRight(char colorOfWhoPushes) {
	if (!checkIfRowFull(-1, -1)) {
		board->getBoardFieldAtXY(x - 1, y + 1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		cout << "MOVE_COMMITED" << endl;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
	}
}