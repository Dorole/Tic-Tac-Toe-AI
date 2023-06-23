#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GameState
{
public:
	void initGrid(char grid[3][3]);
	void initCoordinates(Vector2f coordinates[3][3]);
	bool gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningIndices);
	void switchPlayer(char& currentPlayer);
	void resetVector(vector<Vector2i>& v);
	void resetBool(bool& b, bool value);
	void resetCounter(int& i);
};

