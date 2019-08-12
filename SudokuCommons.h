#include<cstdlib>
#include<iostream>

using namespace std;

int randomGen()
{
	int x = 10;
	while (x > 9)
		x = rand() / ((RAND_MAX + 1u) / 10);
	//cout << x << ",";
	return x;
}

void printBoard(int** matrix)
{
	cout << "Sudoku Board" << endl
		<< " ------- ------- -------" << endl;
	for (int i = 0; i < 9; ++i)
	{
		cout << "|";
		for (int j = 0; j < 9; ++j)
		{
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

bool invalidInRow(int** matrix, int rown, int value)
{
	bool found = false;
	for (int i = 0; i < 9; ++i)
	{
		if (matrix[rown][i] == value)
		{
			found = true;
		}
	}
		return found;
}

bool invalidInColumn(int** matrix, int clmn, int value)
{
	bool found = false;
	for (int i = 0; i < 9; ++i)
	{
		if (matrix[i][clmn] == value)
		{
			found = true;
		}
	}
	return found;
}

bool invalidToPlace(int** matrix, int rown, int clmn, int value)
{
	return invalidInRow(matrix, rown, value) || invalidInColumn(matrix, clmn, value);
}