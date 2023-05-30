#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "Board.h"
#include "BoardField.h"

using namespace std;

Board::Board() {
	board_size = 0;
	pieces_to_trigger = 0;
	GW = 0;
	GB = 0;
	GWreserve = 0;
	GBreserve = 0;
	board_height = 2 * board_size - 1;
	ifRowsWithKRowOnInput = false;
}

Board::Board(int size, int pieces, int GWtoSet, int GBtoSet, int GWres, int GBres, char whose) {
	board_size = size;
	ifRowsWithKRowOnInput = false;
	pieces_to_trigger = pieces;
	GW = GWtoSet;
	GB = GBtoSet;
	GWreserve = GWres;
	GBreserve = GBres;
	whoseTurn = whose;
	board_height = 2 * board_size - 1;
}

void Board::loadInput() {
	cin >> board_size;
	cin >> pieces_to_trigger;
	cin >> GW;
	cin >> GB;
	cin >> GWreserve;
	cin >> GBreserve;
	cin >> whoseTurn;
	board_height = 2 * board_size - 1;
	ifRowsWithKRowOnInput = false;
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

	int x = board_size;
	int y = -board_size;

	int starting_x = x;
	int starting_y = y;

	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < line_length; j++) {
			fields[index].setBoard(this);
			fields[index].setX(x);
			fields[index].setY(y);
			y += 2;
			game_board[i].push_back(fields[index]);
			index++;
		}
		x--;
		if (i < board_size) starting_y--;
		else if (i >= board_size) starting_y++;
		y = starting_y;
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
	cout << board_size << " " << pieces_to_trigger << " " << GW << " " << GB << endl << GWreserve << " " << GBreserve << " " << whoseTurn << endl;
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
	cout << endl;
	//WYPISYWANIE KORDOW
	//how_many_spaces = board_size;
	//cout << endl;
	//for (int i = 0; i < board_height + 2; i++) {
	//	for (int j = 0; j < how_many_spaces; j++) {
	//		cout << " ";
	//	}
	//	if (i < board_size ) how_many_spaces--;
	//	else if (i >= board_size) how_many_spaces++;
	//	for (int j = 0; j < game_board[i].size(); j++) {
	//		cout << game_board[i].at(j).getFirstCoordinate() << game_board[i].at(j).getSecondCoordinate();
	//		if (j != game_board[i].size() - 1) cout << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//WYPISYWANIE KORDOW XY
	//how_many_spaces = board_size;
	//cout << endl;
	//for (int i = 0; i < board_height + 2; i++) {
	//	for (int j = 0; j < how_many_spaces; j++) {
	//		cout << " ";
	//	}
	//	if (i < board_size) how_many_spaces--;
	//	else if (i >= board_size) how_many_spaces++;
	//	for (int j = 0; j < game_board[i].size(); j++) {
	//		cout << "(" << game_board[i].at(j).getX() << "," << game_board[i].at(j).getY() << ")";
	//		if (j != game_board[i].size() - 1) cout << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
	//// WYPISYWANIE MAPY Z BOCZNYMI POLAMI
	//how_many_spaces = board_size;
	//for (int i = 0; i < board_height + 2; i++) {
	//	for (int j = 0; j < how_many_spaces; j++) {
	//		cout << " ";
	//	}
	//	if (i < board_size) how_many_spaces--;
	//	else if (i >= board_size) how_many_spaces++;
	//	for (int j = 0; j < game_board[i].size(); j++) {
	//		cout << game_board[i].at(j).getColor();
	//		if (j != game_board[i].size() - 1) cout << " ";
	//	}
	//	cout << endl;
	//}
	//cout << endl;
}

int Board::howManyRowsOfLengthK() {
	int howManyRows = 0;
	int howManyInSingleRow = 0;
	
	if (checkIfBoardIsCorrect(false)) {
		//DLA CZARNYCH
		//dla poziomu
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size(); j++) {
				if (game_board[i].at(j).getColor() == 'B') {
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size()) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
			}
		}
		//dla przekatnej UPRIGHT
		howManyInSingleRow = 0;
		int x_starting = 0;
		int y_starting = -(board_height - 1);
		int x_pos = x_starting;
		int y_pos = y_starting;
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size()-2; j++) {
				//cout << game_board[i].size() << "(size):  " << x_pos << " " << y_pos << endl;
				if (getBoardFieldAtXY(x_pos,y_pos)->getColor() == 'B') {
					//cout << "How many: " << howManyInSingleRow << endl;
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size()-3) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
				x_pos++;
				y_pos++;
			}
			if (x_starting > -board_size+1) {
				x_starting--;
				y_starting++;
			}
			else y_starting += 2;
			x_pos = x_starting;
			y_pos = y_starting;
		}
		//dla przekatnej DOWNRIGHT
		howManyInSingleRow = 0;
		x_starting = 0;
		y_starting = -(board_height - 1);
		x_pos = x_starting;
		y_pos = y_starting;
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size() - 2; j++) {
				//cout << game_board[i].size() << "(size):  " << x_pos << " " << y_pos << endl;
				if (getBoardFieldAtXY(x_pos, y_pos)->getColor() == 'B') {
					//cout << "How many: " << howManyInSingleRow << endl;
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size() - 3) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
				x_pos--;
				y_pos++;
			}
			if (x_starting < board_size-1) {
				x_starting++;
				y_starting++;
			}
			else y_starting += 2;
			x_pos = x_starting;
			y_pos = y_starting;
		}


		//DLA BIALYCH
		//dla poziomu
		howManyInSingleRow = 0;
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size(); j++) {
				if (game_board[i].at(j).getColor() == 'W') {
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size()) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
			}
		}
		//dla przekatnej UPRIGHT
		howManyInSingleRow = 0;
		x_starting = 0;
		y_starting = -(board_height - 1);
		x_pos = x_starting;
		y_pos = y_starting;
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size() - 2; j++) {
				//cout << game_board[i].size() << "(size):  " << x_pos << " " << y_pos << endl;
				if (getBoardFieldAtXY(x_pos, y_pos)->getColor() == 'W') {
					//cout << "How many: " << howManyInSingleRow << endl;
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size() - 3) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
				x_pos++;
				y_pos++;
			}
			if (x_starting > -board_size + 1) {
				x_starting--;
				y_starting++;
			}
			else y_starting += 2;
			x_pos = x_starting;
			y_pos = y_starting;
		}
		//dla przekatnej DOWNRIGHT
		howManyInSingleRow = 0;
		x_starting = 0;
		y_starting = -(board_height - 1);
		x_pos = x_starting;
		y_pos = y_starting;
		for (int i = 1; i < board_height + 1; i++) {
			howManyInSingleRow = 0;
			for (int j = 0; j < game_board[i].size() - 2; j++) {
				//cout << game_board[i].size() << "(size):  " << x_pos << " " << y_pos << endl;
				if (getBoardFieldAtXY(x_pos, y_pos)->getColor() == 'W') {
					//cout << "How many: " << howManyInSingleRow << endl;
					howManyInSingleRow++;
				}
				else {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
					howManyInSingleRow = 0;
				}
				if (j == game_board[i].size() - 3) {
					if (howManyInSingleRow >= pieces_to_trigger) {
						howManyRows++;
					}
				}
				x_pos--;
				y_pos++;
			}
			if (x_starting < board_size - 1) {
				x_starting++;
				y_starting++;
			}
			else y_starting += 2;
			x_pos = x_starting;
			y_pos = y_starting;
		}
	}
	if (howManyRows != 0) ifRowsWithKRowOnInput = true;
	return howManyRows;
}

bool Board::checkIfBoardIsCorrect(bool ifPrintInfo) {
	int white_on_board = 0;
	int black_on_board = 0;
	if (board_size == 0) return false;
	for (int i = 0; i < board_height; i++) {
		for (int j = 0; j < chars_loaded[i].size(); j++) {
			if (chars_loaded[i].at(j) == 'W') white_on_board++;
			else if (chars_loaded[i].at(j) == 'B') black_on_board++;
		}
	}
	if (white_on_board > GW - GWreserve) {
		if (ifPrintInfo) cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
		return false;
	}
	if (black_on_board > GB - GBreserve) {
		if (ifPrintInfo) cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
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
	if (ifPrintInfo)  cout << "BOARD_STATE_OK" << endl;
	return true;
}

int Board::getBoardSize() const {
	return board_size;
}

bool Board::getIfRowsWithKRowOnInput() const {
	return ifRowsWithKRowOnInput;
}

vector<BoardField>* Board::getGameBoad() const {
	return game_board;
}

BoardField* Board::getBoardFieldAtCords(char first_cord, int second_cord) {
	for (int i = 0; i < board_height+2 ; i++) {
		//cout << i << endl;
		for (int j = 0; j < game_board[i].size(); j++) {
		//	cout << game_board[i].at(j).getFirstCoordinate() << game_board[i].at(j).getSecondCoordinate() << endl;
			if (game_board[i].at(j).getFirstCoordinate() == first_cord && game_board[i].at(j).getSecondCoordinate() == second_cord) {
				return &game_board[i].at(j);
			}
		}
	}
	return nullptr;
}

BoardField* Board::getBoardFieldAtXY(int x, int y) {
	for (int i = 0; i < board_height + 2; i++) {
		for (int j = 0; j < game_board[i].size(); j++) {
			if (game_board[i].at(j).getX() == x && game_board[i].at(j).getY() == y) {
				return &game_board[i].at(j);
			}
		}
	}
	return nullptr;
}

string Board::detectDirection(BoardField first, BoardField second) { // zwraca "NONE" jesli brak kierunku
	if (first.getX() == second.getX() && first.getY() == second.getY() - 2) return "RIGHT";
	if (first.getX() == second.getX() && first.getY() == second.getY() + 2) return "LEFT";
	if (first.getX() == second.getX()+1 && first.getY() == second.getY()-1) return "DOWNRIGHT";
	if (first.getX() == second.getX()+1 && first.getY() == second.getY()+1) return "DOWNLEFT";
	if (first.getX() == second.getX() - 1 && first.getY() == second.getY()-1) return "UPRIGHT";
	if (first.getX() == second.getX() - 1 && first.getY() == second.getY() + 1) return "UPLEFT";
	return "NONE";
}

void Board::changeWhoseTurn() {
	if (whoseTurn == 'B') {
		GBreserve--;
		whoseTurn = 'W';
		return;
	}
	else if (whoseTurn == 'W') {
		GWreserve--;
		whoseTurn = 'B';
		return;
	}
}

void Board::doMove(char FROM_first_cord, int FROM_second_cord, char TO_first_cord, int TO_second_cord) {
	if (getBoardFieldAtCords(FROM_first_cord, FROM_second_cord) == nullptr) {
		cout << "BAD_MOVE_" << FROM_first_cord << FROM_second_cord << "_IS_WRONG_INDEX" << endl;
		return;
	}
	if (getBoardFieldAtCords(TO_first_cord, TO_second_cord) == nullptr) {
		cout << "BAD_MOVE_" << TO_first_cord << TO_second_cord << "_IS_WRONG_INDEX" << endl;
		return;
	}
	else if (getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->getColor() != '+') {
		cout << "BAD_MOVE_" << FROM_first_cord << FROM_second_cord << "_IS_WRONG_STARTING_FIELD" << endl;
		return;
	}
	else if (getBoardFieldAtCords(TO_first_cord, TO_second_cord)->getColor() == '+') {
		cout << "BAD_MOVE_" << TO_first_cord << TO_second_cord << "_IS_WRONG_DESTINATION_FIELD" << endl;
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "NONE") {
		cout << "UNKNOWN_MOVE_DIRECTION" << endl;
		return;
	}

	if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "LEFT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if(getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveLeft('+', true)) changeWhoseTurn();
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "RIGHT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if (getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveRight('+', true)) changeWhoseTurn();
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "UPLEFT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if(getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveUpLeft('+', true)) changeWhoseTurn();
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "UPRIGHT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if(getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveUpRight('+', true))	changeWhoseTurn();
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "DOWNLEFT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if(getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveDownLeft('+', true)) changeWhoseTurn();
		return;
	}
	else if (detectDirection(*getBoardFieldAtCords(FROM_first_cord, FROM_second_cord), *getBoardFieldAtCords(TO_first_cord, TO_second_cord)) == "DOWNRIGHT") {
		getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->setColor(whoseTurn);
		if (getBoardFieldAtCords(FROM_first_cord, FROM_second_cord)->moveDownRight('+', true)) changeWhoseTurn();
		return;
	}


	
}