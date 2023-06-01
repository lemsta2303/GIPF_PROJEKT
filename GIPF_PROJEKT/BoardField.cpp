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

bool BoardField::moveLeft(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x;
	int y_to_move = this->y - 2;
	if (!checkIfRowFull(0,-2)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveLeft(this->color, false);
		board->getBoardFieldAtXY(x_to_move, y_to_move)->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}

bool BoardField::moveRight(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x;
	int y_to_move = this->y + 2;
	if (!checkIfRowFull(0,2)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveRight(this->color, false);
		board->getBoardFieldAtXY(x_to_move, y_to_move)->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}

bool BoardField::moveUpLeft(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x +1;
	int y_to_move = this->y -1;
	if (!checkIfRowFull(1, -1)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveUpLeft(this->color, false);
		board->getBoardFieldAtXY(x+1 , y-1 )->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}

bool BoardField::moveUpRight(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x +1;
	int y_to_move = this->y +1;
	if (!checkIfRowFull(1, 1)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveUpRight(this->color, false);
		board->getBoardFieldAtXY(x + 1, y+1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}

bool BoardField::moveDownLeft(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x -1;
	int y_to_move = this->y -1;
	if (!checkIfRowFull(-1, -1)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveDownLeft(this->color, false);
		board->getBoardFieldAtXY(x - 1, y-1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}

bool BoardField::moveDownRight(char colorOfWhoPushes, bool ifPrintMoveInfo) {
	int x_to_move = this->x-1;
	int y_to_move = this->y+1;
	if (!checkIfRowFull(-1, 1)) {
		if (board->getBoardFieldAtXY(x_to_move, y_to_move)->getColor() != '_') board->getBoardFieldAtXY(x_to_move, y_to_move)->moveDownRight(this->color, false);
		board->getBoardFieldAtXY(x - 1, y + 1)->setColor(color);
		this->setColor(colorOfWhoPushes);
		if (ifPrintMoveInfo) cout << "MOVE_COMMITTED" << endl;
		return true;
	}
	else {
		cout << "BAD_MOVE_ROW_IS_FULL" << endl;
		return false;
	}
}