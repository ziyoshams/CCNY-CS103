/*
 * File name:	ZShamsiddini.cpp
 * Author:		Ziyovuddin Shamsiddini
 * Date:			November 3rd, 2017
 * Description:	Assignment 3 for CSC 103 CC1
 */

#include <sstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <ctime>
using namespace std;

void sanitizeVector(vector<string> &list); // removes duplicates from the given vector;
void populateVector(vector<string> &list, string input);
void print(vector<string> list);																															 // prints out element of a vector
void addDashes(string &shuffled_animals, int num_of_dashes);																	 // adds dashes depending on how many wins or losses you have.
bool inVector(vector<string> animals, string name);																						 // checks if the element is in vector
bool checkInput(vector<string> input_animals, vector<string> picked_animals);									 // takes two vetors and checks if they have expected elements
string getAnimals(vector<string> list, vector<string> &picked_animals, int number_of_animals); // populates another vector with random elements.

int main()
{
	srand(time(NULL));
	bool add_dashes = false;

	string user_input = "";
	string shuffled_animals = "";

	vector<string> animals_list;
	vector<string> picked_animals;
	vector<string> input_animals;

	int num_of_dashes = 0;
	int wins = 0;
	int losses = 0;

	cout << "Enter at least five animal names, e.g., cat, dog, etc..." << endl;

	do
	{
		getline(cin, user_input);
		populateVector(animals_list, user_input);
	} while (!user_input.empty() || animals_list.size() < 5);

	print(animals_list);

	do
	{
		int number_of_animals = rand() % 3 + 1; // number of animals to be picked from the list;
		random_shuffle(animals_list.begin(), animals_list.end());
		shuffled_animals = getAnimals(animals_list, picked_animals, number_of_animals);

		if (add_dashes)
			addDashes(shuffled_animals, num_of_dashes);

		random_shuffle(shuffled_animals.begin(), shuffled_animals.end());
		cout << "What are " << number_of_animals << " animals in \"" << shuffled_animals << "\" ";

		getline(cin, user_input);
		populateVector(input_animals, user_input);
		sanitizeVector(input_animals);

		while (user_input != "quit" &&
					 (user_input == "?" ||
						user_input == "" ||
						input_animals.size() < picked_animals.size() ||
						input_animals.size() > picked_animals.size()))
		{
			if (user_input == "?")
				print(animals_list);

			cout << "Your number of input is incorrect. Enter again: ";
			input_animals.clear();
			getline(cin, user_input);
			populateVector(input_animals, user_input);
			sanitizeVector(input_animals);
		}

		if ((input_animals.size() == picked_animals.size()) && user_input != "quit")
		{
			if (checkInput(input_animals, picked_animals))
			{
				cout << "Yes!" << endl;
				wins++;
				losses = 0;
			}
			else
			{
				cout << "Nope!" << endl;
				losses++;
				wins = 0;
			}

			picked_animals.clear(); // need to clear picked animals for the next round;
			input_animals.clear();

			if (wins == 2)
			{
				wins = 0;
				losses = 0;
				cout << "Succeeded two consecutive times, challenge goes up!" << endl;
				cout << endl;
				num_of_dashes++;
			}
			else if (losses == 2)
			{
				wins = 0;
				losses = 0;
				cout << "Missed two consecutive times, challenge goes down!" << endl;
				cout << endl;
				if (num_of_dashes > 0)
					num_of_dashes--;
			}
		}
		if (num_of_dashes > 0)
			add_dashes = true;
	} while (user_input != "quit");

	cout << "Bye..." << endl;
	return 0;
}
void sanitizeVector(vector<string> &list)
{
	string a;
	for (int i = 0; i < list.size(); i++)
	{
		a = list[i];
		for (int j = i; j < list.size() - 1; j++)
		{
			if (a == list[j + 1])
			{
				list.erase(list.begin() + j);
			}
		}
	}
}

void addDashes(string &shuffled_animals, int num_of_dashes)
{
	int len = shuffled_animals.length();
	int random = rand() % len;
	char dash = '_';

	if (num_of_dashes >= len)
		shuffled_animals.assign(len, '_');
	else
	{
		for (int i = 0; i < num_of_dashes; i++)
		{
			// if picked index is "_" we will pick another index
			while (shuffled_animals[random] == dash)
			{
				random = rand() % len;
			}
			shuffled_animals[random] = dash;
		}
	}
}

bool inVector(vector<string> animals, string name)
{
	for (int i = 0; i < animals.size(); i++)
	{
		if (animals[i] == name)
			return true;
	}
	return false;
}

bool checkInput(vector<string> input_animals, vector<string> picked_animals)
{
	for (int i = 0; i < input_animals.size(); i++)
	{
		if (!inVector(picked_animals, input_animals[i]))
			return false;
	}
	return true;
}

void populateVector(vector<string> &list, string input)
{
	istringstream ss(input);
	string token = "";
	string temp; // stores previuos token;
	while (ss >> token)
	{
		if (token != temp)
			list.push_back(token);
		temp = token;
	}
}

void print(vector<string> list)
{
	for (int i = 0; i < list.size(); i++)
	{
		cout << i + 1 << ": " << list[i] << endl;
	}
}

string getAnimals(vector<string> list, vector<string> &picked_animals, int number_of_animals)
{
	string str = "";
	for (int i = 0; i < number_of_animals; i++)
	{
		str += list[i];
		picked_animals.push_back(list[i]);
	}
	return str;
}
