#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class TextMessages
{

public:
	string displayStartMessage(char currentPlayer);
	string displayWinMessage(char currentPlayer);
	string displayCurrentScore(int score);
	Color setTextColor(char currentPlayer, const Color xColor, const Color oColor);
};

