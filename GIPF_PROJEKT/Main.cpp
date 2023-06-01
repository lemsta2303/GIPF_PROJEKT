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
			//cout << plansza.checkIfBoardIsCorrect(false) << endl;
			//cout << !plansza.getIfRowsWithKRowOnInput();
			if (plansza.getIfBoardCorrect() && !plansza.getIfRowsWithKRowOnInput()) {
				plansza.printBoard();
			}
			else {
			//	cout << "change";
				cout << "EMPTY_BOARD" << endl;
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