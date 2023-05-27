#pragma once

#include <iostream>

using namespace std;

class BoardField {
private:
	char color; // W lub B lub '-' lub '+'
	char first_coordinate;
	int second_coordinate;
public:
	BoardField();
	void setFirstCoordinate(char first);
	void setSecondCoordinate(int second);
	void setColor(char col);
	char getFirstCoordinate() const;
	int getSecondCoordinate() const;
	char getColor() const;

};