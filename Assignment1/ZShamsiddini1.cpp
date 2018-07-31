/* Filename: 	ZShamsiddini1.cpp
 * Author: 		Ziyovuddin Shamsiddini
 * Date:			October 4th, 2017
 * Description:	Assignment 1 for CSC 103. */

#include <iostream>
#include <unistd.h>
using namespace std;
//#define AUTOBET

//  --------- Function Prototypes ----------//
int rollADie();
int getLargest(int number1, int number2);
int autoBet(int humanDie1, int humanDie2, int machineDie1, int machineDie2);
int play(string name, int human1, int human2, int human3);
void printResults(int human, int machine, int &humanMoney, int &machineMoney, int bet);
void printRolledDice(string name, int &large, int die2, int die3);
bool isBigFish(int a, int b, int c);

int main()
{
	srand(time(NULL)); // random seed inserted

	int human;
	int machine;
	int machineMoney = 1000;
	int humanMoney = 1000;

	int humanDie1, humanDie2, humanDie3;
	int machineDie1, machineDie2, machineDie3;

	int bet = 0;
	int round_number_index = 0;

	while ((machineMoney > 0) && (humanMoney > 0))
	{

		humanDie1 = rollADie();
		humanDie2 = rollADie();
		humanDie3 = rollADie();

		machineDie1 = rollADie();
		machineDie2 = rollADie();
		machineDie3 = rollADie();

		cout << "[Round " << ++round_number_index << "] ";
		cout << "You rolled (" << humanDie1 << ", "
				 << humanDie2 << ", "
				 << "?), ";
		cout << "Machine rolled (" << machineDie1 << ", "
				 << machineDie2 << ", "
				 << "?) ..."
				 << endl;

#ifndef AUTOBET
		cout << "How much are you going to bet? ";
		cin >> bet;
#else
		bet = autoBet(humanDie1, humanDie2, machineDie1, machineDie2);
#endif

		// check bet amount
		while ((bet > 10) || (bet <= 0))
		{
			cout << "- your bet must be between $1 and $10, type again: ";
			cin >> bet;
		}

		// start the game
		human = play("You", humanDie1, humanDie2, humanDie3);
		machine = play("Machine", machineDie1, machineDie2, machineDie3);

		printResults(human, machine, humanMoney, machineMoney, bet);
	}
	return 0;
}

int autoBet(int humanDie1, int humanDie2, int machineDie1, int machineDie2)
{
	int betAmount = 1;

	// gets largest of two dice and assigns to separate variables
	int humanLarge = getLargest(humanDie1, humanDie2);
	int machineLarge = getLargest(machineDie1, machineDie2);

	if ((humanDie1 == humanDie2) && (machineDie1 == machineDie2))
	{
		// the chance is that both will have a BIG FISH
		betAmount = 5;
	}
	else if ((humanDie1 == humanDie2) && (machineDie1 != machineDie2))
	{
		// human has better chance for BIG FISH.
		betAmount = 10;
	}
	else if ((humanDie1 != humanDie2) && (machineDie1 == machineDie2))
	{
		// machine has better chance for BIG FISH.
		betAmount = 1;
	}
	else if (humanLarge > machineLarge)
	{
		// set random number between 5 and 9
		betAmount = rand() % 4 + 6;
	}
	else if (machineLarge > humanLarge)
	{
		// set random number between 1 and 5
		betAmount = rand() % 4 + 1;
	}
	return betAmount;
}

int play(string name, int die1, int die2, int die3)
{
	cout << name << " had (" << die1 << ", " << die2 << ", " << die3 << "). ";

	int sum = 0;

	if (isBigFish(die1, die2, die3))
	{
		cout << " ... BIG FISH!!!!" << endl;
		return 50;
	}

	if ((die1 >= die2) && (die1 >= die3))
	{
		sum += die1;
		printRolledDice(name, sum, die2, die3);
	}
	else if ((die2 >= die1) && (die2 >= die3))
	{
		sum += die2;
		printRolledDice(name, sum, die1, die3);
	}
	else
	{
		sum += die3;
		printRolledDice(name, sum, die1, die2);
	}
	cout << "-> " << name << " scored " << sum << endl;
	return sum;
}

void printResults(int human, int machine, int &humanMoney, int &machineMoney, int bet)
{
	if (human == machine)
	{
		cout << "Tied!!! You have $" << humanMoney << ", machine has $" << machineMoney << endl;
		cout << endl;
	}
	else if (human > machine)
	{
		if (human == 50)
		{
			machineMoney = machineMoney - (human * bet);
			humanMoney = humanMoney + (human * bet);
		}
		else
		{
			machineMoney = machineMoney - ((human - machine) * bet);
			humanMoney = humanMoney + ((human - machine) * bet);
		}

		cout << "You won :) You have $" << humanMoney << ", machine has $" << machineMoney << endl;
		cout << endl;
	}
	else
	{
		if (machine == 50)
		{
			humanMoney = humanMoney - (machine * bet);
			machineMoney = machineMoney + (machine * bet);
		}
		else
		{
			humanMoney = humanMoney - ((machine - human) * bet);
			machineMoney = machineMoney + ((machine - human) * bet);
		}

		cout << "You lost :( You have $" << humanMoney << ", machine has $" << machineMoney << endl;
		cout << endl;
	}
}

void printRolledDice(string name, int &sum, int die2, int die3)
{

	die2 = rollADie();
	die3 = rollADie();
	cout << name << " rolled (" << die2 << ", " << die3 << ") ";

	if (die2 >= die3)
	{
		sum += die2;
		die3 = rollADie();
		sum += die3;
		cout << "and then rolled (" << die3 << "). ";
	}
	else
	{
		sum += die3;
		die2 = rollADie();
		sum += die2;
		cout << "and then rolled (" << die2 << "). ";
	}
}

bool isBigFish(int a, int b, int c)
{
	return (a == b) && (a == c);
}

int getLargest(int number1, int number2)
{
	if (number1 > number2)
		return number1;
	else
		return number2;
}

int rollADie()
{
	return rand() % 6 + 1;
}
