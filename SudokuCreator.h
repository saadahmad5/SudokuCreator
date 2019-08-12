#include"SudokuCommons.h"

class Sudoku
{
private:
	const int MAX_ROWS = 9;
	const int MAX_COLUMNS = 9;

	int** matrix;

public:
	Sudoku()
	{
		matrix = new int*[MAX_ROWS];
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			matrix[i] = new int[MAX_COLUMNS];
		}

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
		--x; --y;
		matrix[x][y] = val;

		int i = 0; int j = 0;
		
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				int temp = randomGen();

				if ((x == i) && (y == j))
					cout << matrix[i][j] << " ";
				if ((x != i) || (y != j))
				{
					while (invalidToPlace(matrix, i, j, temp))
					{
						temp = randomGen();
					}
					// cout << temp << " ";
					matrix[i][j] = temp;
					cout << matrix[i][j] << " ";
				}
				//cout << "Processed: (" << i + 1 << "," << j + 1 << ") with value: " << temp << endl;
			}
			cout << endl;
		}

	}
};