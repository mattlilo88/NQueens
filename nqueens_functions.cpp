#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "nqueens.h"

using namespace std;

//Function to place a queen on a given ChessBoard
void insertQueen(ChessBoard *currBoard, int row, int col){
	//At the given row, col of the chessboard(2D vector) set it equal to 1 to 
	//represent a queen placed there and increment numQueens of the given ChessBoard
	currBoard->board[row][col] = 1;
	currBoard->numQueens += 1;
}

//Function to check if given (row, col) is valid for a queen to be placed on ChessBoard
bool checkValid(ChessBoard *currBoard, int row, int col){
	//Checks to see if a space is valid in the whole board
	int size = currBoard->board_size;
	for(int r = 0; r < size; r++){
		//Checks columns of given row to see if a queen is already placed on the column
		if(currBoard->board[r][col] == 1){
			return false;
		}
		//Check positive diagonal of given row, col to see if a queen is already placed on the positive diagonal
		if(row + r < size && col - r >= 0){
			if(currBoard->board[row+r][col-r] == 1){
				return false;
			}
		}
		if(row - r >= 0 && col + r < size){
			if(currBoard->board[row-r][col+r] == 1){
				return false;
			}
		}
		//Check negative diagonal of given row, col to see if a queen is already placed on the negative diagonal
		if(row + r < size && col + r < size){
			if(currBoard->board[row+r][col+r] == 1){
				return false;
			}
		}
		if(row - r >= 0 && col - r >= 0){
			if(currBoard->board[row-r][col-r] == 1){
				return false;
			}
		}
	}
	return true;
}

//Function to solve nqueens on a given ChessBoard
string solve(ChessBoard *currBoard){
	//Create a stack of ChessBoard objects and push the given ChessBoard object onto the stack
	int size = currBoard->board_size;
	stack<class ChessBoard*> recurStack;
	recurStack.push(currBoard);
	string solution = "";

	//While loop to do stack-based recursion
	while(!recurStack.empty()){
		//Pop from top of stack to get ChessBoard object
		ChessBoard *popped = recurStack.top();
		recurStack.pop();

		//Base case where popped ChessBoard object has all the valid placements of queens 
		//Create the solution statement to be returned
		if(popped->numQueens == size){
			for(int r = 0; r < size; r++){
				for(int c = 0; c < size; c++){
					if(popped->board[r][c] == 1){
						solution = solution + to_string(r+1) + " " + to_string(c+1) + " ";
					}
				}
			}
			return solution;
		}

		//Get to a row on the popped ChessBoard object that has no queens on it
		int currRow = 0;
		for(int r = 0; r < size; r++){
			if(count(popped->board[r].begin(), popped->board[r].end(), 1)){
				continue;
			}
			else{
				currRow = r;
				break;
			}
		}

		//Then on that row, check for valid column spaces that queens can be placed on
		//Then for each valid column space, create a new ChessBoard object that copies the 
		//popped ChessBoard object but inserts a new queen at the chosen row, col.
		for(int c = 0; c < size; c++){
			if(checkValid(popped, currRow, c)){
				ChessBoard *to_push = new ChessBoard(size);
				to_push->board_size = size;
				to_push->board = popped->board;
				to_push->numQueens = popped->numQueens;
				insertQueen(to_push, currRow, c);
				recurStack.push(to_push);
			}
		}
	}
	//If while loop ends and nothing is returned, that means No solution could be found from
	//the given ChessBoard
	return "No solution";

}