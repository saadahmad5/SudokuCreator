#include<iostream>
#include<fstream>
#include<ctime>
#include"SudokuCreator.h"

using namespace std;


int main()
{
	cout << "Welcome to Saad's Sudoku Creator" << endl;
	
	//rand function is seeded by time
	srand(time(NULL));

	// Variables
	Sudoku* sudoku = new Sudoku();
	ofstream ofile1, ofile2;
	int x, y, hints ,val;
	string file1, file2;

	/*cout << "Enter coord where you wanna place first value? x ";
	cin >> x;
	cout << "Enter coord where you wanna place first value? y ";
	cin >> y;
	cout << "Enter value: ";
	cin >> val;
	cout << "How many number of hints you want to leave? ";
	cin >> hints;
	*/

	x = 1; y = 1; val = 5;
	hints = 17;


	// For first value placement for randomness
	// params: Row num, Column Num, Value
	sudoku->buildMatrix(x, y, val);

	// To print Randomly created Sudoku
	// params: 2d Matrix
	cout << "Randomly created Grid: " << endl;
	printBoard(sudoku->getMatrix());

	// Make Partial Grid i.e. Sudoku Board
	sudoku->makeSudoku(hints);

	// To print Partial Sudoku board
	// params: 2d Matrix
	cout << "Partial Grid: " << endl;
	printBoard(sudoku->getSudokuMatrix());



	getchar();
	return 0;
}