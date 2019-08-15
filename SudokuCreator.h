#include"SudokuCommons.h"

class Sudoku
{
private:

	int** matrix;
	int** tempmatrix;

	bool CreateRemSudoku(int** mat)
	{
		int row, col;
		
		// Determine if all board is constructed
		if (!FindZero(mat, row, col))
			return true;

		for (int num = 1; num <= 9; num++)
		{
			if (!invalidToPlace(mat, row, col, num))
			{
				mat[row][col] = num;

				if (CreateRemSudoku(mat))
					return true;
				mat[row][col] = 0;
			}
		}
		return false;
	}

public:
	Sudoku()
	{
		matrix = new int*[MAX_ROWS];
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			matrix[i] = new int[MAX_COLUMNS];
		}
		// Defaulting un assigned values as 0
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				matrix[i][j] = 0;
			}
		}
		
		/*
		int grid[9][9] = { {3, 0, 6, 5, 0, 8, 4, 0, 0},
					  {5, 2, 0, 0, 0, 0, 0, 0, 0},
					  {0, 8, 7, 0, 0, 0, 0, 3, 1},
					  {0, 0, 3, 0, 1, 0, 0, 8, 0},
					  {9, 0, 0, 8, 6, 3, 0, 0, 5},
					  {0, 5, 0, 0, 9, 0, 6, 0, 0},
					  {1, 3, 0, 0, 0, 0, 2, 5, 0},
					  {0, 0, 0, 0, 0, 0, 0, 7, 4},
					  {0, 0, 5, 2, 0, 6, 3, 0, 0} };

		*/
	}

	int** getMatrix()
	{
		return matrix;
	}

	int** getSudokuMatrix()
	{
		return tempmatrix;
	}

	void buildMatrix(int x, int y, int val)
	{
		// From human-based-indexing to array-based-index
		--x; --y;
		matrix[x][y] = val;
		
		int i = 0, j = 0, temp;
		for (; j < MAX_COLUMNS; ++j)
		{
			if ((x != i) || (y != j))
			{
				do 
				{
					temp = randomGen();
				} 
				while (invalidToPlace(matrix, i, j, temp));
				matrix[i][j] = temp;
			}
		}
		CreateRemSudoku(matrix);
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

	void makeSudoku(int numHint)
	{

		int leftOver = MAX_ROWS * MAX_COLUMNS - numHint;

		do
		{
			int x = randomGen() % 9;
			int y = randomGen() % 9;
			if (tempmatrix[x][y] != 0)
			{
				int temp = matrix[x][y];
				matrix[x][y] = 0;
				if (SolveSudoku(matrix))
				{
					tempmatrix[x][y] = 0;
				}
				//printBoard(tempmatrix);
			}
		}
		while (countZero(tempmatrix) < leftOver);
	}
};