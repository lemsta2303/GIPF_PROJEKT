#pragma once

#include <vector>
#include <iostream>


using namespace std;

class BoardField;

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
	vector<char>* chars_loaded;
	vector<BoardField>* game_board;
	bool ifRowsWithKRowOnInput;
public:
	Board();
	Board(int size, int pieces, int GW, int GB, int GWres, int GBres, char whose);
	void loadInput();
	void loadBoard();
	void createGameBoard();
	void printBoard();
	int howManyRowsOfLengthK();
	bool checkIfBoardIsCorrect(bool ifPrintInfo);
	int getBoardSize() const;
	bool getIfRowsWithKRowOnInput() const;
	vector<BoardField>* getGameBoad() const;
	BoardField* getBoardFieldAtCords(char first_cord, int second_cord);
	BoardField* getBoardFieldAtXY(int x, int y);
	string detectDirection(BoardField first, BoardField second);
	void changeWhoseTurn();
	void doMove(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord);

};