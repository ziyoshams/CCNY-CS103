/*
 * Filename: ZShamsiddini5.cpp
 * Author: Ziyovuddin Shamsiddini
 * Date: November 30, 2017
 * Description: Assignment 5 for CSC 103 CC1
 */

#ifdef __WIN32__
#include <windows.h>

#define sleep(n) Sleep(1000 * n)
#endif

#ifdef __APPLE__
#include <unistd.h>
#endif

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
using namespace std;

void print(vector<vector<string>> const &vect);														 // Prints existing 2D vector;
void createVector(vector<vector<string>> &vect, int row, int col);				 // creates 2D vector with numberes.
void insertRandomSymbols(vector<vector<string>> &vect, int row, int col);	// creates and inserts random character pairs.
string getChar(vector<vector<string>> const &vect, int col, int position); // returns a char from given coordinates
bool isTimeOut(int start, int now, int timeAllowed);											 // returns bool whether time is passed allowed time.

int main()
{
	srand(time(NULL));
	vector<bool> matchedPositions; // records matched positions //
	vector<vector<string>> maskVector;
	vector<vector<string>> symbolsVector;
	int row = 0;
	int col = 0;
	int product = 0;
	int firstSlot = 0;
	int secondSlot = 0;

	cout << "In this game, pairs of letters will be hidden on a rectangular grid." << endl;
	cout << "Once the grid is established you will be asked to enter the number of two slots." << endl;
	cout << "If the letters at those slots match, they will stay in view." << endl;
	cout << "If not, after 3 seconds the letters will disappear and be replaced by the numbers." << endl;
	cout << "You job is to find all the pairs\n\n\n"
			 << endl;

	do
	{
		cout << "Size reqiurement: product of row x col must be between 16 and 64 and be even" << endl;
		cout << "Enter rows: ";
		cin >> row;
		cout << "Enter columns: ";
		cin >> col;
		cout << endl;
		product = row * col;
	} while (product < 16 || product > 64 || product % 2 != 0);

	for (int i = 0; i < product; i++)
		matchedPositions.push_back(false);

	createVector(maskVector, row, col);

	int timeAllowed = (product / 4) * 60;
	int min = timeAllowed / 60;
	int sec = timeAllowed % 60;
	int numPairs = product / 2;
	int guessedPairCounter = 0; // if guessedPairCounter == numPairs You win //

	cout << "Allowing 30 seconds per pair" << endl;
	cout << "You will have " << min << " minutes and " << sec << " seconds to find the " << numPairs << " pairs" << endl;
	cout << "Let\'s play" << endl;
	cout << endl;

	insertRandomSymbols(symbolsVector, row, col);
	int startTime = time(0);
	int now = 0;
	while (!isTimeOut(startTime, now, timeAllowed) && guessedPairCounter < numPairs)
	{

		print(maskVector);
		cout << "\n\n"
				 << endl;

		do
		{
			cout << "Enter first slot to view: ";
			cin >> firstSlot;
		} while (firstSlot > product || firstSlot < 1);

		do
		{
			cout << "Enter second slot to view: ";
			cin >> secondSlot;
		} while (secondSlot > product || secondSlot < 1 || secondSlot == firstSlot);

		string a = getChar(symbolsVector, col, firstSlot);
		string b = getChar(symbolsVector, col, secondSlot);

		int x, y;
		int xVal1, yVal1; // to store positions and reverse the matrix to previous state;
		int tempPos = firstSlot;
		tempPos = tempPos - 1; // slot numbers start from 1, so we need to decrement it
		x = tempPos / col;
		y = tempPos % col;
		xVal1 = x;
		yVal1 = y;
		string tempValue1 = maskVector[x][y]; // will swap the prev value back if no match
		maskVector[x][y] = a;

		int xVal2, yVal2; // to store positions and reverse the matrix to previous state;
		tempPos = secondSlot;
		tempPos = tempPos - 1;
		x = tempPos / col;
		y = tempPos % col;
		xVal2 = x;
		yVal2 = y;
		string tempValue2 = maskVector[x][y]; // will swap the prev value back if no match
		maskVector[x][y] = b;

		print(maskVector);

		if (a == b)
		{
			if (matchedPositions[firstSlot - 1] == true && matchedPositions[secondSlot - 1] == true)
			{
				cout << "Previously matched" << endl;
			}
			else
			{
				cout << "\a"
						 << "Match" << endl;
				matchedPositions[firstSlot - 1] = true;
				matchedPositions[secondSlot - 1] = true;
				guessedPairCounter++;
			}
		}
		else
		{
			cout << "No Match" << endl;
			// revert the matrix to previous state
			maskVector[xVal1][yVal1] = tempValue1;
			maskVector[xVal2][yVal2] = tempValue2;
		}
		now = time(0);
		if (!isTimeOut(startTime, now, timeAllowed) && guessedPairCounter != numPairs)
		{
			sleep(3);
			for (int i = 0; i < 100; i++)
				cout << endl;
		}
	}

	if (isTimeOut(startTime, now, timeAllowed) && guessedPairCounter != numPairs)
	{
		cout << "\nTime has expired" << endl;
		cout << "You revealed: " << endl;
		print(maskVector);
		cout << endl;
		cout << "All the pairs were at:" << endl;
		print(symbolsVector);
	}
	else if (guessedPairCounter == numPairs)
	{
		int completed = now - startTime;
		int mins = completed / 60;
		int secs = completed % 60;
		cout << "All matched within " << mins << " minutes and " << secs << " seconds." << endl;
	}

	return 0;
}

bool isTimeOut(int start, int now, int timeAllowed)
{
	return (now - start) >= timeAllowed;
}

string getChar(vector<vector<string>> const &vect, int col, int position)
{
	int x, y;
	position -= 1;
	// determine x and y coordinates of the matrix
	x = position / col;
	y = position % col;
	return vect[x][y];
}

void createVector(vector<vector<string>> &vect, int row, int col)
{
	int index = 1;
	for (int i = 0; i < row; i++)
	{
		vector<string> temp;
		for (int j = 0; j < col; j++)
		{
			temp.push_back(to_string(index));
			index++;
		}
		vect.push_back(temp);
	}
}

void insertRandomSymbols(vector<vector<string>> &vect, int row, int col)
{

	// I will put symbols in 1D vector first, then shuffle it, then add elements to 2D vector
	int symbol = 65; // will be transformed into symbol
	int count = 0;
	int range = row * col;
	int index = 0;
	char c;
	vector<string> temp1D;

	for (int j = 0; j < range; j++)
	{
		c = char(symbol);
		temp1D.push_back(string(1, c));
		count++;
		if (count == 2)
		{
			symbol++;
			count = 0;
		}
	}

	random_shuffle(temp1D.begin(), temp1D.end());

	for (int i = 0; i < row; i++)
	{
		vector<string> temp;
		for (int j = 0; j < col; j++)
		{
			temp.push_back(temp1D[index]);
			index++;
		}
		vect.push_back(temp);
	}
}

void print(vector<vector<string>> const &vect)
{
	string space = "";
	for (auto x : vect)
	{
		cout << "  ";
		for (auto y : x)
		{
			if (y.length() == 1)
				space = " ";
			cout << space << y << "  ";
			space = "";
		}
		cout << endl;
	}
}
