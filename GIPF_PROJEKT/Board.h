#pragma once

#include <vector>
#include <iostream>

#include "BoardField.h"

using namespace std;

class Board {
private:
	int board_size; // dlugosc jednego boku szesciokata
	int pieces_to_trigger; // liczba pionow ktora wyzwala zbieranie pioow - musi byc wieksza niz 1 i mniejsza od (2*board_size - 1)
	int GW; // liczba pionow gracza bialego
	int GB; // liczba pionow gracza czarnego
	int GWreserve; // liczba pionow gracza bialego w rezerwie;
	int GBreserve; // liczba pionow gracza czarnego w rezerwie;
	char whoseTurn; // kogo aktualnie tura
	int board_height;
	bool if_checked;
	vector<char>* chars_loaded;
	vector<BoardField>* game_board;
public:
	Board();
	Board(int size, int pieces, int GW, int GB, int GWres, int GBres, char whose);
	void loadInput();
	void loadBoard();

	void createGameBoard();


	void printBoard();
	bool checkIfBoardIsCorrect(bool ifPrintInfo);

	int getBoardSize() const;
	bool getIfChecked() const;

};