/* File: ZShamsiddini4.cpp
 * Author: Ziyovuddin Shamsiddini
 * Date: November 19th, 2017
 * Description: Assignment 4 for CSC 103 CC1
 */

#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;
void populateVector(vector<string> &words, string input); // Takes a long string and plucks each word and puts in a vector
void createLine(vector<string> temp, string &word);				// Prepares a line to be printed out of given vector
void addSpaces(vector<string> &temp, int remSpace);				// Adds needed spaces to the words endings

int main()
{
	vector<string> words;
	vector<string> temp;
	string word = "";
	string input = "";
	string dashes = "";
	int width = 0;
	int remSpace = 0;
	int wordCount = 0;
	int lineLength = 0;
	int totalLength = 0;

	cout << "Enter text, empty return will quit the input" << endl;
	do
	{
		getline(cin, input);
		populateVector(words, input);
	} while (!input.empty());

	cout << "Enter the width of text: ";
	cin >> width;
	cout << endl;

	while (width != 0)
	{
		dashes.assign(width, '-');
		cout << "|" << dashes << "|" << endl;

		for (int i = 0; i < words.size(); i++)
		{
			wordCount++;
			totalLength = totalLength + words[i].length();

			if ((totalLength + wordCount - 1) < width)
			{
				temp.push_back(words[i]);
				lineLength = lineLength + words[i].length();
			}
			else if (words[i].length() >= width)
			{
				remSpace = width - lineLength;
				if (temp.size() == 0)
				{
					temp.push_back(words[i]);
					createLine(temp, word);
				}
				else
				{
					addSpaces(temp, remSpace);
					createLine(temp, word);
				}
				cout << "|" << word << "|" << endl;
				word = "";
				wordCount = 0;
				lineLength = 0;
				totalLength = 0;
				temp.erase(temp.begin(), temp.end());
			}
			else
			{
				i--;
				remSpace = width - lineLength; // remaining space
				addSpaces(temp, remSpace);
				createLine(temp, word);

				cout << "|" << word << "|" << endl;
				word = "";
				wordCount = 0;
				lineLength = 0;
				totalLength = 0;
				temp.erase(temp.begin(), temp.end());
			}
		}

		if (temp.size() > 0)
		{
			remSpace = width - lineLength; // remaining space
			addSpaces(temp, remSpace);
			createLine(temp, word);
			cout << "|" << word << "|" << endl;
			word = "";
			wordCount = 0;
			lineLength = 0;
			totalLength = 0;
			temp.erase(temp.begin(), temp.end());
		}

		cout << "|" << dashes << "|" << endl;
		cout << "Enter the width of text: ";
		cin >> width;
		cout << endl;
	}

	return 0;
}

void addSpaces(vector<string> &temp, int remSpace)
{
	while (remSpace > 0)
	{
		if (temp.size() > 1)
		{
			for (int j = 0; j < temp.size() - 1; j++)
			{
				if (remSpace != 0)
				{
					temp[j] += " ";
					remSpace--;
				}
			}
		}
		else
		{
			for (int k = 0; k < temp.size(); k++)
			{
				if (remSpace != 0)
				{
					temp[k] += " ";
					remSpace--;
				}
			}
		}
	}
}

void createLine(vector<string> temp, string &word)
{
	for (int l = 0; l < temp.size(); l++)
		word += temp[l];
}

void populateVector(vector<string> &words, string input)
{
	string word = "";
	for (int i = 0; i < input.length(); i++)
	{
		if (!isspace(input[i]))
		{
			word += input[i];
		}
		else
		{
			if (!word.empty()) // make sure there is no more than 1 space betweeen words.
				words.push_back(word);

			word = "";
		}
	}
	if (!word.empty())
		words.push_back(word);
}
