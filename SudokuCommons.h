
/*
* Written by: Saad Ahmad
* Date created: 7th of August
* Date modified: 16th of August
* Program: Sudoku
* Description: Sudoku common methods
*/


#include<cstdlib>
#include <algorithm>
#include<iostream>

using namespace std;

const int MAX_ROWS = 9;
const int MAX_COLUMNS = 9;

// Returns random number
// params: none
// returns: a random number
int randomGen()
{
	int x = 10;
	while (x > 9)
		x = rand() / ((RAND_MAX + 1u) / 10);
	return x;
}

// Prints the Sudoku board given the matrix
// params: 2D matrix 9x9
// returns: nothing
void printBoard(int** matrix)
{
	cout << " ------- ------- -------" << endl;
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		cout << "|";
		for (int j = 0; j < MAX_COLUMNS; ++j)
		{
			if (matrix[i][j] == 0)
				cout << "  ";
			else
				cout << " " << matrix[i][j];
			if (j % 3 == 2) 
			{
				cout << " |";
			}
		}
		cout << endl;
		if (i % 3 == 2)
		{
			cout << " ------- ------- ------- " << endl;
		}
	}
}

// Tells whether a number can be placed in a row?
// params: matrix, the row number and that value
// returns: true or false based on decision

bool invalidInRow(int** matrix, int rown, int value)
{
	bool found = false;
	for (int i = 0; i < MAX_ROWS; ++i)
	{
		if (matrix[rown][i] == value)
		{
			found = true;
		}
	}
		return found;
}

// Tells whether a number can be placed in a column?
// params: matrix, the col number and that value
// returns: true or false based on decision

bool invalidInColumn(int** matrix, int clmn, int value)
{
	bool found = false;
	for (int i = 0; i < MAX_COLUMNS; ++i)
	{
		if (matrix[i][clmn] == value)
		{
			found = true;
		}
	}
	return found;
}

// Tells whether a number can be placed in a box?
// params: matrix, the start row, the start col number and that value
// returns: true or false based on decision

bool invalidInBox(int** matrix, int boxStartRow, int boxStartCol, int value)
{
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 3; col++)
		{
			if (matrix[row + boxStartRow][col + boxStartCol] == value)
				return true;
		}
	}
	return false;
}


// Takes above three functions and tells in conjunction to them
// params: 2D matrix, row number, column number, value
// returns: true or false based on decision

bool invalidToPlace(int** matrix, int rown, int clmn, int value)
{
	return invalidInRow(matrix, rown, value) || invalidInColumn(matrix, clmn, value) || invalidInBox(matrix, rown - rown % 3, clmn - clmn % 3, value);
}

// Tells whether a Sudoku is fully filled?
// params: 2d matrix, row , and column
// returns: true or false based on decision

bool FindZero(int** matrix, int &row, int &col)
{
	for (row = 0; row < MAX_ROWS; row++)
		for (col = 0; col < MAX_COLUMNS; col++)
			if (matrix[row][col] == 0)
				return true;
	return false;
}


