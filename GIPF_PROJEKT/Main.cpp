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
			if (plansza.howManyRowsOfLengthKWithCapturing(false) != 0 ) {
				if(plansza.howManyRowsOfLengthKWithCapturing(false) == 1) cout << "ERROR_FOUND_" << plansza.howManyRowsOfLengthKWithCapturing(false) << "_ROW_OF_LENGTH_K" << endl;
				if(plansza.howManyRowsOfLengthKWithCapturing(false) > 1) cout << "ERROR_FOUND_" << plansza.howManyRowsOfLengthKWithCapturing(false) << "_ROWS_OF_LENGTH_K" << endl;
			}
			else plansza.checkIfBoardIsCorrect(true);
		}
		else if (command == "PRINT_GAME_BOARD") {
			if (plansza.getIfBoardCorrect() && !plansza.getIfRowsWithKRowOnInput()) {
				plansza.printBoard();
			}
			else {
				cout << "EMPTY_BOARD" << endl;
			}
		}
		else if (command.substr(0, 7) == "DO_MOVE") {
			char priorityFirst_firstCord = 'x';
			int priorityFirst_secondCord = -1;
			char prioritySecond_firstCord = 'x';
			int prioritySecond_secondCord = -1;
			char priorityColor = 'x';
			if (command.length() > 13) {
				priorityFirst_firstCord = command[17];
				priorityFirst_secondCord = int(command[18]) - 48;
				prioritySecond_firstCord = command[20];
				prioritySecond_secondCord = int(command[21]) - 48;
				priorityColor = command[14];
			}
			plansza.doMove(command[8], int(command[9])-48, command[11], int(command[12])-48, priorityFirst_firstCord, priorityFirst_secondCord, prioritySecond_firstCord, prioritySecond_secondCord, priorityColor);
		}
		else if (command == "PRINT_GAME_STATE") {
			cout << plansza.getGameState();
		}
	}
	return;
}

int main() {
	gameControlling();
	return 0;
}