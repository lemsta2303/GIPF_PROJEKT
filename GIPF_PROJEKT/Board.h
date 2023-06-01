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
	bool ifBoardCorrect;
public:
	Board();
	Board(int size, int pieces, int GW, int GB, int GWres, int GBres, char whose);
	void loadInput();
	void loadBoard();
	void createGameBoard();
	void printBoard();
	void capturing(int x_pos, int y_pos, int x_dir, int y_dir, char color, bool ifPriorityCapturing);
	string detectDirectionInPriorityCapturing(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord);
	int getDistanceBetweenTwoFields(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord, char color);
	void priorityCapturing(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord, char color);
	int howManyRowsOfLengthKWithCapturing(bool capturing);
	bool checkIfBoardIsCorrect(bool ifPrintInfo);
	void setIfBoardCorrect(bool ifCorrect);
	int getBoardSize() const;
	bool getIfBoardCorrect() const;
	bool getIfRowsWithKRowOnInput() const;
	vector<BoardField>* getGameBoad() const;
	BoardField* getBoardFieldAtCords(char first_cord, int second_cord);
	BoardField* getBoardFieldAtXY(int x, int y);
	string detectDirection(BoardField first, BoardField second);
	void changeWhoseTurn();
	bool checkIfPriorityCapturingCorrect(char FROM_first_cord, int FROM_second_cord, char priorityFirst_firstCord, int priorityFirst_secondCord, char prioritySecond_firstCord, int prioritySecond_secondCord, char priorityColor, string direction);
	void doMove(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord, char priorityFirst_firstCord, int priorityFirst_secondCord, char prioritySecond_firstCord, int prioritySecond_secondCord, char priorityColor);

};