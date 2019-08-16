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
	int rhints, hints ,val;
	string file1, file2;

	cout << "Enter the first value you want to place at (1,1) coord? ";
	cin >> val;
	cout << "How many number of hints you want to leave? ";
	cin >> rhints;
	cout << "Enter the partial matrix output file name: ";
	cin >> file1;
	cout << "Enter the console output and stats file name: ";
	cin >> file2;
	
	// For debugging default vals
	/*file1 = "pSudoku2.dat";
	file2 = "statSdk2.dat";
	val = 5;
	hints = 17;*/


	// For first value placement for randomness
	// params: Row num, Column Num, Value
	beforeCreate = GetTickCount();
	sudoku->buildMatrix(val);


	// To print Randomly created Sudoku
	// params: 2d Matrix
	cout << "Randomly created Grid: " << endl;
	printBoard(sudoku->getSudokuMatrix());


	// Make Partial Grid i.e. Sudoku Board
	//sudoku->makeSudoku();
	cout << "Partial Grid: (Be Patient!)" << endl;
	
	sudoku->makeSudoku(rhints);
	afterCreate = GetTickCount();

	// To print Partial Sudoku board
	// params: 2d Matrix
	printBoard(sudoku->getMatrix());

	
	hints = (MAX_ROWS * MAX_COLUMNS) - sudoku->countZero(sudoku->getMatrix());

	// Just to debug and see that partial matrix solves to mine matrix
	/*SolveSudoku(sudoku->getMatrix()); // From Mohamad Darwiche code
	cout << "After solving this partial matrix: " << endl;
	printBoard(sudoku->getMatrix());*/

	// Statistical data
	cout << endl << "================ Statistical Data ================" << endl
		<< "The number of hints requested were: " << rhints << endl
		<< "But the given Sudoku created provided hints " << hints << endl
		<< "Number of Recursive steps for creating Sudoku puzzle: "
		 << countOfRecursiveSteps << endl
		 << "Time elapsed during creation of Sudoku is " 
		 << (afterCreate - beforeCreate) << " in milliSeconds" << endl
		 << "Count of BackTracking is "
	   	 << countOfBackTrack << endl
		 << "Number of Random Number Hits on Sudoku board: " << hits << endl
		<< "Number of Random Number Miss on Sudoku board: " << miss << endl;



	ofile1.open(file1);
	if (ofile1)
	{
		int** SdkMat = sudoku->getMatrix();
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
		ofile2 << "The co-ordinate for first value is (1,1) and value placed is: "
			<< val << endl 
			<< "The number of hints to leave are: " << hints << endl
			<< "The file name for partial matrix output file name: "
			<< file2 << endl << endl
			<< "The CONSTRUCTED Matrix is: " << endl << endl;
		int** SdkMat = sudoku->getSudokuMatrix();
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
		SdkMat = sudoku->getMatrix();
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

	ofile2  << endl << "================ Statistical Data ================" << endl
			<< "The number of hints requested were: " << rhints << endl
			<< "But the given Sudoku created provided hints " << hints << endl
			<< "Number of Recursive steps for creating Sudoku puzzle: "
			<< countOfRecursiveSteps << endl
			<< "Time elapsed during creation of Sudoku is "
			<< (afterCreate - beforeCreate) << " in milliSeconds" << endl
			<< "Count of BackTracking is " 
			<< countOfBackTrack << endl
			<< "Number of Random Number Hits on Sudoku board: " << hits << endl
			<< "Number of Random Number Miss on Sudoku board: " << miss << endl;

	}
	else
	{
		cout << "File I/O error" << endl;
	}
	ofile2.close();
	cout << endl << "Press any key to exit to Windows ... ";
	getchar();
	return 0;
}