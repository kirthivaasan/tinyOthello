/**
    @author Kirthivaasan Puniamurthy
*/
#include <iostream>
class Othello {
	public:
		Othello() {
			for (int i = 0; i < 8; i++) for (int j = 0; j < 8; j++) board[i][j] = 0;	// zeros out board array.
			board[3][3] =  board[4][4] = -1;
			board[4][3] =  board[3][4] = 1;
		}
		bool place(int player, char col, int row) {
			return makeMove(player, charToInt(col), 8 - row);
		}
		bool ai(int player) {
			for (int i = 0; i < 8; ++i) for (int j = 0; j < 8; ++j) if (makeMove(player, i, j)) return true;
			return false;
		}
		char intToPlayer(int player) {
			if (player == 0) return ' ';
			if (player == -1) return 'O';
			if (player == 1) return 'X';
		}
		void render() {
			std::string line =  " |---+---+---+---+---+---+---+---|";
			for (int row = 8; row >= 1; row--) {
				std::cout << line << std::endl << row;
				for (int col = 0; col < 8; col++) std::cout << "| " << intToPlayer(board[8 - row][col]) << " ";
				std::cout << "|" << std::endl;
			}
			std::cout << line << std::endl << "   a   b   c   d   e   f   g   h" << std::endl;
		}
		void getScore(int &x, int &o) {
			x = 0; o = 0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (board[i][j] == 1) x += 1;
					if (board[i][j] == -1) o += 1;
				}
			}
		}
	private:
		bool makeMove(int player,int col, int row) {
			if ( inBounds(row, col) && board[row][col] == 0) { // check bounds and if spot is empty.
				if ( flip(player, row, col) ) {
					board[row][col] = player;
					return true;
				}
			}
			return false;
		}
		bool inBounds(int row, int col) { return row >= 0 && row < 8 && col >= 0 && col < 8; }
		bool flip(int player, int row, int col, int d_row, int d_col, bool playerNeighbourCheck=false) {
			row += d_row;
			col += d_col;
			int current = board[row][col];
			if (!inBounds(row, col) || current == 0)		return false;						// current is out of bounds or blank
			if (current == player && !playerNeighbourCheck)	return true;						// current is player piece but not original player pos
			if (current == -1*player && flip(player, row, col, d_row, d_col, false)) {	// current has to be opp piece, call flipHelper.
				board[row][col] = player;
				return true;
			}
		}
		bool flip(int player, int r, int c) {
			bool valid[8] = { flip(player, r, c, -1, 0), flip(player, r, c,  1, 0), flip(player, r, c, 0, -1), flip(player, r, c, -1, 1),
							  flip(player, r, c,  0, 1), flip(player, r, c,  1, 1), flip(player, r, c,-1, -1), flip(player, r, c, 1, -1)};
			for (int i = 0; i < 8; i++) if (valid[i]) return true;
			return false;
		}
		int charToInt(char c) { if (c >= 'a' && c <= 'h') return (int)c - 97; return -1; }
		int board[8][8];
};