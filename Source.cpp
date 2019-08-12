#include<iostream>
#include<ctime>
#include"SudokuCreator.h"

using namespace std;


int main()
{
	srand(time(NULL));
	
	/*
	int val = 0;
	while (val < 10)
	{
		int random = randomGen();
		cout << random << " ";
		if (random == val)
		{
			cout << endl;
			val++;
		}
	}
	*/

	Sudoku* sudoku = new Sudoku();
	int x, y, val;
	/*cout << "Enter coord where you wanna place first value? x ";
	cin >> x;
	cout << "Enter coord where you wanna place first value? y ";
	cin >> y;
	cout << "Enter value: ";
	cin >> val;*/

	// For first value placement
	sudoku->buildMatrix(2,2,8);
	printBoard(sudoku->getMatrix());


	getchar();
	return 0;
}