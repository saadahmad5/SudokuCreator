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

	// MY PROGRAM IS EFFICIENT. The first row is generated, keeping rules in mind
	// by just putting random values. The rows from 2 to 9 are created by back track
	// mechanism.

	// Method that creates the Suduko matrix from row 2 to 9
	// param: matrix
	bool CreateRemSudoku(int** mat)
	{
		countOfBackTrack++;
		int row, col;
		
		// Even a single zero in matrix means board is incomplete
		// Determine if all board is constructed
		// params: int** matrix, int row, int col
		if (!FindZero(mat, row, col)) {
			return true;
		}
			
		// Trying values from 1 to 9 that fits in matrix
		for (int num = 1; num <= 9; num++)
		{
			if (!invalidToPlace(mat, row, col, num))
			{
				hits++;
				mat[row][col] = num;

				// Recursion occurs here
				if (CreateRemSudoku(mat)) 
				{
					countOfRecursiveSteps++;
					return true;
				}
				mat[row][col] = 0;
			}
			else
			{
				miss++;
			}
		}
		return false;
	}

	// Tells how many solutions can be computed given a partial matrix
	void numSolutions(int &numSol)
	{
		int row, col;


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
	int** getMatrix()
	{
		return matrix;
	}

	int** getSudokuMatrix()
	{
		return tempmatrix;
	}

	void buildMatrix(int val)
	{

		int i = 0, j = 0, temp;
		matrix[i][j] = val;
		for (j = 1; j < MAX_COLUMNS; ++j)
		{
			do 
			{
				temp = randomGen();
			} 
			while (invalidToPlace(matrix, i, j, temp));
			matrix[i][j] = temp;
		}
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