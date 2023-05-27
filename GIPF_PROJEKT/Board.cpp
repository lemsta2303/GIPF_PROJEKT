#include <iostream>
#include <vector>

#include "Board.h"

using namespace std;

Board::Board() {
	board_size = 0;
	pieces_to_trigger = 0;
	GW = 0;
	GB = 0;
	GWreserve = 0;
	GBreserve = 0;
	board_height = 2 * board_size - 1;
	if_checked = false;
}

Board::Board(int size, int pieces, int GWtoSet, int GBtoSet, int GWres, int GBres, char whose) {
	board_size = size;
	pieces_to_trigger = pieces;
	GW = GWtoSet;
	GB = GBtoSet;
	GWreserve = GWres;
	GBreserve = GBres;
	whoseTurn = whose;
	board_height = 2 * board_size - 1;
	if_checked = false;
}

void Board::loadInput() {
	if_checked = false;
	cin >> board_size;
	cin >> pieces_to_trigger;
	cin >> GW;
	cin >> GB;
	cin >> GWreserve;
	cin >> GBreserve;
	cin >> whoseTurn;
	board_height = 2 * board_size - 1;
	loadBoard();
}

void Board::loadBoard() {
	if (board_size != 0)chars_loaded = new vector<char>[board_height];
	else return;
	char c = getchar(); // wylapanie new lanea po komendzie
	c = 'x';
	for (int i = 0; i < board_height; i++) {
		c = 'x';
		while (int(c) != 10 && int(c) != EOF) {
			c = getchar();
			if (int(c) != 32 && int(c) != 10) {
				chars_loaded[i].push_back(c);
			}
		}
	}
	if(checkIfBoardIsCorrect(false)) createGameBoard();
}

void Board::createGameBoard() {
	int how_many_fields_needed = 0;
	for (int i = 2 * board_size; i >= board_size + 1; i--) {
		how_many_fields_needed += 2 * i;
	}
	how_many_fields_needed += board_size * 2 + 1;
	BoardField* fields = new BoardField[how_many_fields_needed];
	int index = 0;
	game_board = new vector<BoardField>[board_height + 2];
	int line_length = board_size + 1;
	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < line_length; j++) {
			game_board[i].push_back(fields[index]);
			index++;
		}
		if (i < board_size) line_length++;
		else if (i >= board_size) line_length--;
	}

	char starting_first_cord = 'a';
	int starting_second_cord = board_size + 1;

	char first_cord = 'a';
	int second_cord = board_size+1;

	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < game_board[i].size(); j++) {
			game_board[i].at(j).setFirstCoordinate(first_cord);
			game_board[i].at(j).setSecondCoordinate(second_cord);
			first_cord = char(first_cord + 1);
			if (i <= board_size) {
				if (j < board_size) second_cord++;
			}
			else if (i > board_size) {
				if (j < board_size - (i - board_size)) second_cord++;
			}
		}
		if (i < board_size) {
			first_cord = starting_first_cord;
			starting_second_cord--;
			second_cord = starting_second_cord;
		}
		if (i >= board_size) {
			starting_first_cord = char(starting_first_cord + 1);
			first_cord = starting_first_cord;
			second_cord = starting_second_cord;
		}
	}
	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < game_board[i].size(); j++) {
			if (i == 0 || i == board_height + 1 || j == 0 || j == game_board[i].size()-1) {
				game_board[i].at(j).setColor('+');
			}
			else{
				game_board[i].at(j).setColor(chars_loaded[i - 1].at(j - 1));
			}
		}
	}
}


void Board::printBoard() {
	int how_many_spaces = board_size - 1;
	for (int i = 1; i < board_height + 1; i++) {
		for (int j = 0; j < how_many_spaces; j++) {
			cout << " ";
		}
		if (i < board_size) how_many_spaces--;
		else if (i >= board_size) how_many_spaces++;


		for (int j = 1; j < game_board[i].size() - 1; j++) {
			cout << game_board[i].at(j).getColor();
			if (j != game_board[i].size() - 1) cout << " ";
		}
		cout << endl;
	}
	/*WYPISYWANIE KORDOW
	how_many_spaces = board_size;
	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < how_many_spaces; j++) {
			cout << " ";
		}
		if (i < board_size ) how_many_spaces--;
		else if (i >= board_size) how_many_spaces++;
		for (int j = 0; j < game_board[i].size(); j++) {
			cout << game_board[i].at(j).getFirstCoordinate() << game_board[i].at(j).getSecondCoordinate();
			if (j != game_board[i].size() - 1) cout << " ";
		}
		cout << endl;
	}
	cout << endl << endl;
	 WYPISYWANIE MAPY Z BOCZNYMI POLAMI
	how_many_spaces = board_size;
	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < how_many_spaces; j++) {
			cout << " ";
		}
		if (i < board_size) how_many_spaces--;
		else if (i >= board_size) how_many_spaces++;
		for (int j = 0; j < game_board[i].size(); j++) {
			cout << game_board[i].at(j).getColor();
			if (j != game_board[i].size() - 1) cout << " ";
		}
		cout << endl;
	}
	cout << endl << endl;*/
}

bool Board::checkIfBoardIsCorrect(bool ifPrintInfo) {
	if_checked = true;
	int white_on_board = 0;
	int black_on_board = 0;
	if (board_size == 0) return false;
	for (int i = 0; i < board_height; i++) {
		for (int j = 0; j < chars_loaded[i].size(); j++) {
			if (chars_loaded[i].at(j) == 'W') white_on_board++;
			else if (chars_loaded[i].at(j) == 'B') black_on_board++;
		}
	}
	if (white_on_board != GW - GWreserve) {
		if (ifPrintInfo) cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
		return false;
	}
	if (black_on_board != GB - GBreserve) {
		if(ifPrintInfo) cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
		return false;
	}
	//sprawdzanie czy odpowiednia dlugosc bokow
	int k = board_size;
	for (int i = 0; i < board_height; i++) {
		if (chars_loaded[i].size() != k) {
			if (ifPrintInfo) cout << "WRONG_BOARD_ROW_LENGTH" << endl;
			return false;
		}
		else {
			if (i < board_size-1) k++;
			else if (i >= board_size-1) k--;
		}
	}
	if (ifPrintInfo) cout << "BOARD_STATE_OK" << endl;
	return true;
}

int  Board::getBoardSize() const {
	return board_size;
}

bool Board::getIfChecked() const {
	return if_checked;
}