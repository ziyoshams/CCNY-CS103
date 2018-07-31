/* Filename:	ZShamsiddini2.cpp
 * Author:	Ziyovuddin Shamsiddini
 * Date:		October 23rd, 2017
 * Description: Assignment2 for CSC 103 CC1
 */

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

string getSecretWord(const vector<string> &wList);
void printWord(string dashes);																	 // prints dashes with guessed word;
void swapIt(string secret, char input, string &str, int &count); // swaps _ with a guessed letter;
void startTheGame(vector<string> &words);
void playAgain(bool &play_again);
bool letterExist(string text, char letter);
bool isTimeOut(int start, int now, int timeAllowed, bool &timeout);

int main()
{
	srand(time(NULL));
	bool play_again = false;
	vector<string> words = {"variable", "function", "object", "expression", "plus",
				"pattern", "module", "debug", "integrated", "development",
				"environment", "virtual", "input", "shift", "constructor",
				"destructor", "syntax", "iterate", "procedure", "compiler"};

	cout << "You are about to play Hangman." << endl;
	cout << "You will see an underscore in place of every letter within the word" << endl;
	cout << "You win if you guess the word, within" << endl;
	cout << "\tmaximum guesses equal to 2 times the letters within the word or a minimum of ten, which ever is larger" << endl;
	cout << "\tand a time limit of 7 seconds times the letters within the word or a minimum of 40 seconds, which ever is larger" << endl;

	do
	{
		startTheGame(words);
		playAgain(play_again);

	} while (play_again);

	return 0;
}

void startTheGame(vector<string> &words)
{
	string dashes;
	string guessedLetters = "";
	string secret = getSecretWord(words);
	int secret_length = secret.length();
	int timeStart = time(0);
	int count = 0;
	int numberOfGuesses = 0;
	int guessAmount = 10;
	if (secret_length * 2 > 10)
		guessAmount = secret_length * 2;

	int timeAllowed = 40;
	if (secret_length * 7 > 40)
		timeAllowed = secret_length * 7;

	bool timeout = false;
	bool completed = false;
	char input;

	dashes.assign(secret_length, '_');
	while (!completed && (numberOfGuesses < guessAmount) && !isTimeOut(timeStart, time(0), timeAllowed, timeout))
	{
		printWord(dashes);
		cout << "Enter a letter: ";
		cin >> input;

		if (!letterExist(guessedLetters, input))
		{
			numberOfGuesses++;
		}
		else
		{
			cout << input << " is on of previously guessed letters: " << guessedLetters << endl;
		}

		if (letterExist(secret, input) && !letterExist(guessedLetters, input))
		{
			swapIt(secret, input, dashes, count);
			guessedLetters += input; // fixed after submiting the assignment !!!
		}

		if (count == secret_length)
		{
			completed = true;
		}
	}

	if ((numberOfGuesses >= guessAmount) && !completed)
	{
		cout << "You exceeded " << guessAmount << " tries." << endl;
		cout << "The word was " << secret << endl;
	}
	else if (timeout)
	{
		cout << "You exceeded " << timeAllowed << " seconds to guess the word." << endl;
		cout << "The word was " << secret << endl;
	}
	else if (completed)
	{
		cout << "Congratulations! You guessed " << secret << " in " << numberOfGuesses << " tries." << endl;
	}
}

void printWord(string dashes)
{
	for (int i = 0; i < dashes.length(); i++)
	{
		cout << dashes[i] << ' ';
	}
	cout << endl;
}

void playAgain(bool &play_again)
{
	char answer;
	cout << "\nDo you want to play again (y/n)? ";
	cin >> answer;
	while (answer != 'y' && answer != 'n')
	{
		cout << "\nDo you want to play again (y/n)? ";
		cin >> answer;
	}
	if (answer == 'y')
		play_again = true;
	else if (answer == 'n')
		play_again = false;
}

void swapIt(string secret, char input, string &str, int &count)
{
	for (int i = 0; i < secret.length(); i++)
	{
		if (secret[i] == input)
		{
			str[i] = input;
			count++;
		}
	}
}

bool letterExist(string text, char letter)
{
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == letter)
			return true;
	}
	return false;
}

bool isTimeOut(int start, int now, int timeAllowed, bool &timeout)
{
	if ((now - start) > timeAllowed)
	{
		timeout = true;
		return true;
	}
	return false;
}

string getSecretWord(const vector<string> &wList)
{
	int vectorSize = wList.size();
	int random = rand() % vectorSize;
	return wList[random];
}
