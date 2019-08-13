#include"SudokuCommons.h"

class Sudoku
{
private:

	int** matrix;


	bool CreateRemSudoku(int** mat)
	{
		int row, col;
		
		// Determine if all board is constructed
		if (!FindZero(mat, row, col))
			return true;

		// Sudoku Numbers 1 to 9  
		for (int num = 1; num <= 9; num++)
		{
			if (!invalidToPlace(mat, row, col, num))
			{
				mat[row][col] = num;
				// Recursive Back-track call
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
	}

	int** getMatrix()
	{
		return matrix;
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
	}
};