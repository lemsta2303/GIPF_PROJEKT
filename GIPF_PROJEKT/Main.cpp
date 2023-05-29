#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "Board.h"

using namespace std;

void gameControlling() {
	string command;
	string commandInMoving;
	string coordinatesOfMoving;
	Board plansza;
	while(!cin.eof()){
		getline(std::cin, command);
		if (command == "LOAD_GAME_BOARD") {
			plansza.loadInput();
			plansza.checkIfBoardIsCorrect(true);
		}
		else if (command == "PRINT_GAME_BOARD") {
			if (plansza.checkIfBoardIsCorrect(false)) {
				plansza.printBoard();
			}
		}
		else if (command.substr(0, 7) == "DO_MOVE") {
			plansza.doMove(command[8], int(command[9])-48, command[11], int(command[12])-48);
		}
	}
	return;
}

int main() {
	gameControlling();
	return 0;
}