/**
    @author Kirthivaasan Puniamurthy
*/

#include <iostream>
#include <vector>
#include <cstdlib>

class Othello {
	public:
		Othello();
		bool place(int player, char col, int row); // this function is called by the player.
		bool ai(int player);
		char intToPlayer(int player);
		void render();
		void getScore(int &x, int &o);
	private:
		bool makeMove(int player,int col, int row);
		bool inBounds(int row, int col);
		bool flip(int player, int row, int col, std::vector<int> &track, bool validMove);
		bool flipHelper(int player, int row, int col, int d_row, int d_col, bool playerNeighbourCheck);
		int charToInt(char c);
		int board[8][8];
};

Othello::Othello() {
	for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) board[i][j] = 0;	// zeros out board array.
	board[3][3] =  board[4][4] = -1;
	board[4][3] =  board[3][4] = 1;
}

char Othello::intToPlayer(int player) {
	if (player == 0) return ' ';
	if (player == -1) return 'O';
	if (player == 1) return 'X';
}

bool Othello::inBounds(int row, int col) {
	return row >= 0 && row < 8 && col >= 0 && col < 8;
}

void Othello::getScore(int &x, int &o) {
	x = 0;
	o = 0;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == 1) x += 1;
			if (board[i][j] == -1) o += 1;
		}
	}
}

bool Othello::ai(int player) {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j)
			if (makeMove(player, i, j)) return true;
	}
	return false;
}

bool Othello::flipHelper(int player, int row, int col, int d_row, int d_col, bool playerNeighbourCheck=true) {
	row += d_row;
	col += d_col;
	int current = board[row][col];
	if (!inBounds(row, col) || current == 0)		return false;						// current is out of bounds or blank
	if (current == player && !playerNeighbourCheck)	return true;						// current is player piece but not original player pos
	if (current == -1 * player && flipHelper(player, row, col, d_row, d_col, false)) {	// current has to be opp piece, call flipHelper.
		board[row][col] = player;
		return true;
	}
}

bool Othello::flip(int player, int row, int col, std::vector<int> &track, bool validMove=false) {
	if (track.size() == 2)
		return flipHelper(player, row, col, track[0], track[1]);
	for (int i = -1; i < 2; i++) {
		track.push_back(i);
		validMove = flip(player, row, col, track, validMove) || validMove;
		track.pop_back();
	}
	return validMove;
}

int Othello::charToInt(char c) {
	if (c >= 'a' && c <= 'h') return (int)c - 97;
	return -1;
}

bool Othello::place(int player, char col, int row) {
	return makeMove(player, charToInt(col), 8 - row);
}

bool Othello::makeMove(int player, int col, int row) {
	if ( inBounds(row, col) && board[row][col] == 0) { // check bounds and if spot is empty.
		std::vector<int> track;
		if ( flip(player, row, col, track) ) {
			board[row][col] = player;
			return true;
		}
	}
	return false;
}

void Othello::render() {
	int row_count = 0, board_num = 8;
	std::cout << std::endl;
	for (int row = 1; row <= 17; row++) {
		if (row % 2 != 0) {
			std::cout << " |---+---+---+---+---+---+---+---|" << std::endl;
		} else {
			for (int col = 0; col <= 8; col++) {
				if (col == 0) {
					std::cout << board_num << "| " << intToPlayer(board[row_count][col]);
					board_num -= 1;
				} else if (col < 8) {
					std::cout << " | " << intToPlayer(board[row_count][col]);
				} else {
					std::cout << " |";	
				}
			}
			std::cout << std::endl;
			row_count += 1;
		}
	}
	std::cout << "   a   b   c   d   e   f   g   h" << std::endl;
}