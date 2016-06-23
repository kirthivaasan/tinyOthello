/**
    @author Kirthivaasan Puniamurthy
*/

#include <iostream>
#include <cstdlib>
#include "Othello.cc"

int main() {
	Othello othello_game;
	int player = 1; // 1 = 'X', -1 = 'O'
	std::string row, col;
	std::string message = "Welcome to othello.";
	int x = 0;
	int o = 0;
	bool ai = false; // default is no ai.
	do {
		system("cls"); // system("clear") for linux
		othello_game.render();
		othello_game.getScore(x, o);
		std::cout << " Current player: " << othello_game.intToPlayer(player) << "\n X = " << x << " O = " << o 
				<< std::endl << " " << message << std::endl << " >> ";
		std::cin >> col;
		
		if (col == "ai" && !ai) {
			ai = true;
			player *= -1;
			if (!othello_game.ai(-1 * player))
				message = "Computer could not find a move.";
		} else if (col == "quit" || col == "exit") {
			message = "Quit.";
		} else if (col == "save") {
			message = "Board saved.";
		} else if (col == "load") {
			message = "Board loaded.";
		} else {
			std::cin >> row;
			int row_int = atoi(row.c_str());
			if ( othello_game.place(player, col.c_str()[0], row_int) ) {
				message = "Made move [" + col + ", " + row + "]";
				if (ai) {
					if (!othello_game.ai(-1 * player)) 
						message = "Computer could not find a move."; 
					else
						player *= -1;
			} else {
				message = "That move does not flip any pieces / Coordinates out of bound.";
			}
		}			
	} while (col != "quit" && col != "exit");
}