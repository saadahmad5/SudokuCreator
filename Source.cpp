#include<iostream>
#include<fstream>
#include<ctime>
#include<string>
#include<iomanip>
#include <windows.h>
#include"SudokuCreator.h"

using namespace std;


int main()
{
	cout << "Welcome to Saad's Sudoku Creator" << endl;
	
	//rand function is seeded by time
	srand(time(NULL));

	// Variables
	DWORD beforeCreate;
	DWORD afterCreate;
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
	cout << "Enter the partial matrix output file name: ";
	cin >> file1;
	cout << "Enter the console output and stats file name: ";
	cin >> file2;
	*/

	file1 = "pSudoku2.dat";
	file2 = "statSdk2.dat";
	x = 1; y = 1; val = 5;
	hints = 17;


	// For first value placement for randomness
	// params: Row num, Column Num, Value
	beforeCreate = GetTickCount();
	sudoku->buildMatrix(x, y, val);


	// To print Randomly created Sudoku
	// params: 2d Matrix
	cout << "Randomly created Grid: " << endl;
	printBoard(sudoku->getMatrix());

	// Make Partial Grid i.e. Sudoku Board
	sudoku->makeSudoku(hints);
	afterCreate = GetTickCount();
	// To print Partial Sudoku board
	// params: 2d Matrix
	cout << "Partial Grid: " << endl;
	printBoard(sudoku->getSudokuMatrix());

	cout << "Number of Recursive steps for creating Sudoku puzzle: "
		 << countOfRecursiveSteps << endl
		 << "Time elapsed during creation of Sudoku is " 
		 << (afterCreate - beforeCreate) << " in milliSeconds" << endl
		 << "Count of BackTracking is "
	   	 << countOfBackTrack << endl;



	ofile1.open(file1);
	if (ofile1)
	{
		int** SdkMat = sudoku->getSudokuMatrix();
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				if(SdkMat[i][j] != 0)
					ofile1 << i + 1 << " " << j + 1 << " " << SdkMat[i][j] << endl;
			}
		}
		cout << "Partial Matrix output to: " << file1 << endl;
	}
	else
	{
		cout << "File I/O error" << endl;
	}
	ofile1.close();

	ofile2.open(file2);
	if (ofile2)
	{
		ofile2 << "The co-ordinate for first value is (" << x << ", " << y
			<< ")" << endl << "The value placed is: " << val << endl 
			<< "The number of hints to leave are: " << hints << endl
			<< "The file name for partial matrix output file name: "
			<< file2 << endl << endl
			<< "The CONSTRUCTED Matrix is: " << endl << endl;
		int** SdkMat = sudoku->getMatrix();
		ofile2 << " ------- ------- -------" << endl;
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			ofile2 << "|";
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				if (SdkMat[i][j] == 0)
					ofile2 << "  ";
				else
					ofile2 << " " << SdkMat[i][j];
				if (j % 3 == 2)
				{
					ofile2 << " |";
				}
			}
			ofile2 << endl;
			if (i % 3 == 2)
			{
				ofile2 << " ------- ------- ------- " << endl;
			}
		}
		SdkMat = sudoku->getSudokuMatrix();
		ofile2 << endl << "The PARTIAL Matrix is: " << endl << endl
			   << " ------- ------- -------" << endl;
		for (int i = 0; i < MAX_ROWS; ++i)
		{
			ofile2 << "|";
			for (int j = 0; j < MAX_COLUMNS; ++j)
			{
				if (SdkMat[i][j] == 0)
					ofile2 << "  ";
				else
					ofile2 << " " << SdkMat[i][j];
				if (j % 3 == 2)
				{
					ofile2 << " |";
				}
			}
			ofile2 << endl;
			if (i % 3 == 2)
			{
				ofile2 << " ------- ------- ------- " << endl;
			}
		}

		ofile2 << "Number of Recursive steps for creating Sudoku puzzle: "
			<< countOfRecursiveSteps << endl
			<< "Time elapsed during creation of Sudoku is "
			<< (afterCreate - beforeCreate) << " in milliSeconds" << endl
			<< "Count of BackTracking is " 
			<< countOfBackTrack << endl;

	}
	else
	{
		cout << "File I/O error" << endl;
	}
	ofile2.close();
	cout << "Press any key to exit to Windows ... ";
	getchar();
	return 0;
}