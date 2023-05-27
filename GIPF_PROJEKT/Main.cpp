#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "Board.h"

using namespace std;

void gameControlling() {
	string komenda;
	Board plansza;
	while(!cin.eof()){
		getline(std::cin, komenda);
		if (komenda == "LOAD_GAME_BOARD") {
			plansza.loadInput();
			plansza.checkIfBoardIsCorrect(true);
		}
		else if (komenda == "PRINT_GAME_BOARD") {
			if (plansza.checkIfBoardIsCorrect(false)) {
				plansza.printBoard();
			}
		}
	}
	return;
}

int main() {
	gameControlling();

	return 0;
}