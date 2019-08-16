
/*
* Written by: Saad Ahmad
* Date created: 7th of August
* Date modified: 16th of August
* Program: Sudoku
* Description: Sudoku creator methods/ data
*/

// including common funtions
#include"SudokuCommons.h"

// For keeping record of metrics
static int countOfRecursiveSteps = 0;
static int countOfBackTrack = 0;
static int hits = 0;
static int miss = 0;

class Sudoku
{
private:

	// Two matrices; partial solution and generated solution
	int** matrix;
	int** tempmatrix;
	bool devM;

	// MY PROGRAM IS EFFICIENT. The first row is generated, keeping rules in mind
	// by just putting random values. The rows from 2 to 9 are created by back track
	// mechanism. Less stack single calls (81 - 9 = 72) are used!

	// Method that creates the Suduko matrix from row 2 to 9
	// params: matrix
	// returns: fills up and generates a random sudoku board
	bool CreateRemSudoku(int** mat)
	{
		countOfBackTrack++;
		int row, col;
		
		// Even a single zero in matrix means board is incomplete
		// Determine if all board is constructed
		// params: int** matrix, int row, int col
		if (!FindZero(mat, row, col)) 
		{
			if (devM)
				cout << endl;
			return true;
		}


			
		// Trying values from 1 to 9 that fits in matrix
		for (int num = 1; num <= 9; num++)
		{


			if (!invalidToPlace(mat, row, col, num))
			{
				hits++;
				mat[row][col] = num;
				
				if (devM)
					cout << mat[row][col] << ", ";

				// Recursion occurs here
				if (CreateRemSudoku(mat)) 
				{
					countOfRecursiveSteps++;
					return true;
				}
				mat[row][col] = 0;
				if (devM)
					cout << endl << "[" << row+1 << "][" << col+1 << "]" << endl;
			}
			else
			{
				miss++;
			}
		}

		return false;
	}

	// Tells how many solutions can be computed given a partial matrix
	// params: aliased variable numberOfSols
	// return: nothing but processes numberOfSols a Sudoku can have
	void numSolutions(int &numSol)
	{
		int row, col;

		// If no Zero in matrix, Sudoku is solved
		if (!FindZero(matrix, row, col))
		{
			numSol++;
			return;
		}


		for (int i = 0; i < MAX_ROWS; i++)
		{
			if (numSol < 2)
			{
				if (!invalidToPlace(matrix, row, col, i + 1))
				{
					matrix[row][col] = i + 1;
					numSolutions(numSol);
				}
			}
			matrix[row][col] = 0;
		}

	}


public:
	// Constructor
	// params: nothing
	// returns: nothing but constructs and defaults to 0 to 81 places 
	Sudoku()
	{
		matrix = new int*[MAX_ROWS];
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			matrix[i] = new int[MAX_COLUMNS];
		}
		// Defaulting un-assigned values to 0
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				matrix[i][j] = 0;
			}
		}
		
	}

	// Getter funtions
	//
	int** getMatrix()
	{
		return matrix;
	}

	int** getSudokuMatrix()
	{
		return tempmatrix;
	}

	// Builds a complete sudoku board
	// params: takes a bool whether to activate Dev mode and value at 1,1
	// returns: nothing
	void buildMatrix(int val, bool devM)
	{
		// All couts for debugging purposes only
		this->devM = devM;
		int i = 0, j = 0, temp;
		if (devM) 
			cout << "For Debugging purposes only: " << endl;
		matrix[i][j] = val;
		if (devM)
			cout << matrix[i][j] << ", ";

		// Randomly generates and puts values on matrix conforming to rules
		for (j = 1; j < MAX_COLUMNS; ++j)
		{
			do 
			{
				temp = randomGen();
			} 
			while (invalidToPlace(matrix, i, j, temp));
			matrix[i][j] = temp;
			if (devM)
				cout << matrix[i][j] << ", ";
		}
		if (devM)
			cout << endl;
		CreateRemSudoku(matrix);

		// Copying the created matrix to tempMatrix because later
		// I am changing the same matrix to partial matrix

		tempmatrix = new int*[MAX_ROWS];
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			tempmatrix[i] = new int[MAX_COLUMNS];
		}

		// Defaulting un assigned values as 0
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				tempmatrix[i][j] = matrix[i][j];
			}
		}
	}

	// Makes partial sudoku by evicting one value at a time and checking whether has unique sol
	// params: int hint number of hints to leave on board
	// returns: nothing
	void makeSudoku(int hint)
	{
		hint = MAX_ROWS * MAX_COLUMNS - hint;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int temp = matrix[i][j];
				matrix[i][j] = 0;

				// If multiple solutions, replace the value back.
				// Otherwise, it is removed
				int check = 0;
				numSolutions(check);
				if (check != 1)
				{
					matrix[i][j] = temp;
				}

				if (countZero(matrix) >= hint)
				{
					return;
				}
			}
		}
	}

	// Calculates the number of non-hints
	// params: partial matrix 
	// returns: number of non-hints
	int countZero(int** matrix)
	{
		int count = 0;
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				if (matrix[i][j] == 0)
					++count;
			}
		}
		return count;
	}
};