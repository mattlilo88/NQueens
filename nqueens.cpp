#include <iostream>
#include <stack>
#include <stdexcept>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "nqueens.h"

using namespace std;


int main(int argc, char**argv)
{
	//Checks if user provides two valid arugments, if not throw an error message
	if(argc != 3){
		throw std::invalid_argument("Usage: ./nqueens <INPUT FILE> <OUTPUT FILE>");
	}

	//Stream for input and output files
	ifstream input;
	ofstream output;

	input.open(argv[1]);
	output.open(argv[2]);

	//Used to store each line of input
	string inputLine;


	//Loop through the input file, processing each line and solving nqueens
	while(getline(input, inputLine)){
		//Since we don't know how long a given line is, use stringstream to process the line
		stringstream s(inputLine);
		string numInput;
		int count = 0;

		//Go through a given line of input, pushing each integer into a vector<int>
		vector<int> currLine;
		while(s >> numInput){
			currLine.push_back(stoi(numInput));
			count+=1;
		}
		//If number of inputs in the line is an even number, it's invalid. 
		if(count % 2 == 0){
			output << "No solution" << endl;
			continue;
		}
		//Create a ChessBoard object with a chessboard(2D vector) of int size
		int size = currLine[0];
		ChessBoard *currBoard = new ChessBoard(size);
		
		//If there was only one int given from the input line, that means there were not any
		//given queen placements. Place one for the given board size.
		if(count == 1){
			if(size == 4 || size == 6){
				insertQueen(currBoard, 0, 1);
			}
			else{
				insertQueen(currBoard, 0, 0);
			}
		}
		else{
			//Go through the length of the line of inputs(stored in vector)
			int invalidCheck = 0;
			for(int i = 1; i < currLine.size() - 1; i += 2){
				//Get the row and col from the input line
				int row = currLine[i];
				int col = currLine[i+1];
				//Check if at the given chessboard(2D vector) there is already a queen at the row given above
				//If so, then it's an invalid placement and the chessboard is invalid
				if(std::count(currBoard->board[row-1].begin(), currBoard->board[row-1].end(), 1)){
					invalidCheck += 1;
					break;
				}	
				//Check if at the given chessboard(2D vector) if the given row and col above can have a queen 
				//placed there. If not, then it's an invalid placement and the chessboard is invalid
				if(!checkValid(currBoard, row-1, col-1)){
					invalidCheck += 1;
					break;
				}
				//If the given row and col above is valid to be placed, place a queen on the ChessBoard
				insertQueen(currBoard, row-1, col-1);
			}
			//Used to write "No solution" if one of the invalid cases is met above
			if(invalidCheck == 1){
				output << "No solution" << endl;
				continue;
			}
		}
		
		//Call solve on the initial ChessBoard, and set solution equal to the correct queen placements
		//or No solution
		string solution = solve(currBoard);

		//Write the solution to the output file
		output << solution << endl;
		
	}
	//Close input and output files
	input.close();
	output.close();

}