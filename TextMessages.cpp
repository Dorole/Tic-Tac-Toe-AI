#include <SFML/Graphics.hpp>
#include <string>
#include "TextMessages.h"

using namespace std;
using namespace sf;

string TextMessages::displayStartMessage(char currentPlayer)
{
	string s{};
	s.push_back(currentPlayer);

	return s + " starts!";
}

string TextMessages::displayWinMessage(char currentPlayer)
{
	string s{};
	s.push_back(currentPlayer);

	return s + " won!";
}

Color TextMessages::setTextColor(char currentPlayer, const Color xColor, const Color oColor)
{
	return currentPlayer == 'x' ? xColor : oColor;
}

string TextMessages::displayCurrentScore(int score)
{
	return to_string(score);
}
