#pragma once

#include <iostream>

#include "BoardField.h"

using namespace std;

BoardField::BoardField() {
	color = '-';
	first_coordinate = 'x';
	second_coordinate = -1;
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

