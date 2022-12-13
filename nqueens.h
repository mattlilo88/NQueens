#ifndef NQUEENS_H
#define NQUEENS_H

#include <vector>
#include <string>

using namespace std;

class ChessBoard{
	public:
		int board_size; //Variable to store size of the board
		vector<vector<int>> board; //2D vector to store the board
		int numQueens = 0; //variable to store number of queens on the board

		//Constructor to build the chessboard(2D vector) given a size
		ChessBoard(int size){ 
			vector<int> col(size, 0);
			for(int i = 0; i < size; i++){
				board.push_back(col);
			}
			board_size = size;
		}
};

void insertQueen(ChessBoard*, int, int);	
bool checkValid(ChessBoard*, int, int);
string solve(ChessBoard*);

#endif
