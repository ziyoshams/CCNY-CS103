#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

void createDeckOfCards(vector<string> &vect);
void print(vector<string> const vect);

class Player
{
public:
	Player();
	virtual void chooseDiscard(int pos)
	{
		discard = hand[pos];
		discardIndex = pos;
		discardList[index] = discard;
	};

	void replenish();

	int getPlayerIndex() { return index; }
	string getDisCard() { return discard; }
	void setCards(vector<string> &cards);
	void printCards();
	bool isWinner();
	virtual ~Player(){};

protected:
	vector<string> hand; //holds 7 cards
	string discard;			 //card being discarded
	int discardIndex;		 //position within hand of card being discarded
	int index;
	static int selfIndex; //index within player vector, starting with 0 for the human
	static string discardList[];
};

class AutoPlayer : public Player
{
public:
	AutoPlayer() { index = ++selfIndex; }
	virtual void chooseDiscard()
	{
		int pos = rand() % 7;
		discard = hand[pos];
		discardIndex = pos;
		discardList[index] = discard;
	};
};

int Player::selfIndex = 0;
string Player::discardList[5];

Player::Player()
{
	for (int i = 0; i < 7; i++)
	{
		hand.push_back("");
	}
	index = selfIndex;
	discardIndex = 0;
}

void Player::replenish()
{
	int i = index - 1;
	if (i < 0)
		i = 4;
	hand[discardIndex] = discardList[i];
}

void Player::setCards(vector<string> &cards)
{
	for (int i = 0; i < cards.size(); i++)
	{
		hand[i] = cards[i];
	}
}

void Player::printCards()
{
	string space = "    ";
	for (int i = 0; i < 7; i++)
	{
		if (hand[i].length() > 2)
			space = "   ";
		else
			space = "    ";
		cout << space << hand[i];
	}
	cout << endl;
}

bool Player::isWinner()
{
	for (int i = 0; i < hand.size() - 1; i++)
	{
		string a = hand[0], b = hand[i + 1];

		if (a[0] != b[0])
			return false;
	}
	cout << "Player " << index << " is winner!" << endl;
	return true;
}

int main()
{
	srand(time(NULL));
	vector<string> cards, options;
	vector<string> card1, card2, card3, card4, card5;

	Player human;
	AutoPlayer bot1, bot2, bot3, bot4;
	vector<Player *> players = {&human, &bot1, &bot2, &bot3, &bot4};
	options = {" a", " b", " c", " d", " e", " f", " g"};
	createDeckOfCards(cards);
	random_shuffle(cards.begin(), cards.end());

	for (int i = 0; i < 7; i++)
	{
		card1.push_back(cards[i]);
		card2.push_back(cards[i + 7]);
		card3.push_back(cards[i + 14]);
		card4.push_back(cards[i + 21]);
		card5.push_back(cards[i + 28]);
	}
	human.setCards(card1);
	bot1.setCards(card2);
	bot2.setCards(card3);
	bot3.setCards(card4);
	bot4.setCards(card5);

	char choice;
	do
	{
		cout << "Your hand:" << endl;
		cout << human.getPlayerIndex() << ":\t";
		human.printCards();
		print(options);
		do
		{
			cin >> choice;
			if ((choice < 'a' || choice > 'g') && choice != '?')
				cout << "Invalid choice" << endl;
		} while ((choice < 'a' || choice > 'g') && choice != '?');

		if (choice == '?')
		{
			for (int i = 0; i < players.size(); i++)
			{
				cout << players[i]->getPlayerIndex() << ":\t";
				players[i]->printCards();
			}
		}
		else
		{
			human.chooseDiscard(int(choice) - 97);
			bot1.chooseDiscard();
			bot2.chooseDiscard();
			bot3.chooseDiscard();
			bot4.chooseDiscard();
			cout << "\t"
					 << "Player 0 gave 1 " << human.getDisCard() << endl;
			cout << "\t"
					 << "Player 1 gave 2 " << bot1.getDisCard() << endl;
			cout << "\t"
					 << "Player 2 gave 3 " << bot2.getDisCard() << endl;
			cout << "\t"
					 << "Player 3 gave 4 " << bot3.getDisCard() << endl;
			cout << "\t"
					 << "Player 4 gave 0 " << bot4.getDisCard() << endl;

			for (int i = 0; i < players.size(); i++)
			{
				players[i]->replenish();
			}
		}

	} while (!(human.isWinner() ||
						 bot1.isWinner() ||
						 bot2.isWinner() ||
						 bot3.isWinner() ||
						 bot4.isWinner()));

	cout << "At the end of the game the players had:" << endl;
	for (int i = 0; i < players.size(); i++)
	{
		players[i]->printCards();
	}

	return 0;
}

void print(vector<string> const vect)
{
	cout << "\t";
	for (int i = 0; i < vect.size(); i++)
	{
		cout << "    " << vect[i];
	}
	cout << endl;
}

void createDeckOfCards(vector<string> &vect)
{
	string sym = "";
	for (int i = 1; i < 14; i++)
	{
		if (i < 10)
		{
			vect.push_back("H" + to_string(i + 1));
			vect.push_back("D" + to_string(i + 1));
			vect.push_back("S" + to_string(i + 1));
			vect.push_back("C" + to_string(i + 1));
		}
		else if (i == 10)
		{
			sym = "A";
			vect.push_back("H" + sym);
			vect.push_back("D" + sym);
			vect.push_back("S" + sym);
			vect.push_back("C" + sym);
		}
		else if (i == 11)
		{
			sym = "J";
			vect.push_back("H" + sym);
			vect.push_back("D" + sym);
			vect.push_back("S" + sym);
			vect.push_back("C" + sym);
		}
		else if (i == 12)
		{
			sym = "Q";
			vect.push_back("H" + sym);
			vect.push_back("D" + sym);
			vect.push_back("S" + sym);
			vect.push_back("C" + sym);
		}
		else if (i == 13)
		{
			sym = "K";
			vect.push_back("H" + sym);
			vect.push_back("D" + sym);
			vect.push_back("S" + sym);
			vect.push_back("C" + sym);
		}
	}
}
