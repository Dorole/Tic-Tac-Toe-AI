#include "GameState.h"
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

void GameState::initGrid(char grid[3][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			grid[i][j] = ' ';
		}
	}
}

void GameState::initCoordinates(Vector2f coordinates[3][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		float incrementY = i * 300;

		for (size_t j = 0; j < 3; j++)
		{
			float incrementX = j * 300;

			coordinates[j][i] = Vector2f(incrementX, incrementY);
		}
	}
}

void GameState::switchPlayer(char& currentPlayer)
{
	currentPlayer == 'x' ? currentPlayer = 'o' : currentPlayer = 'x';
}

bool GameState::gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningIndices)
{
	//check columns
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] != ' ' && grid[i][0] == currentPlayer && (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]))
		{
			cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;

			for (size_t j = 0; j < 3; j++)
				winningIndices.push_back(Vector2i(i, j));

			return true;
		}
	}

	//check rows
	for (int j = 0; j < 3; j++)
	{
		if (grid[0][j] != ' ' && grid[0][j] == currentPlayer && (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]))
		{
			cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;

			for (size_t i = 0; i < 3; i++)
				winningIndices.push_back(Vector2i(i, j));

			return true;
		}
	}

	//check diagonals
	if (grid[1][1] != ' ' && grid[1][1] == currentPlayer &&
		((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
			(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])))
	{
		cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;

		if (grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		{
			for (size_t i = 0; i < 3; i++)
				winningIndices.push_back(Vector2i(i, i));
		}
		else
		{
			for (size_t i = 0, j = 2; i < 3; i++, j--)
			{
				winningIndices.push_back(Vector2i(i, j));
			}
		}


		return true;
	}

	//check for empty spaces
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[i][j] == ' ')
				return false;
		}
	}

	//all fields full, but no winner
	cout << "\n********** Wow, you're equally good! **********" << endl;
	return true;
}

void GameState::resetVector(vector<Vector2i>& v)
{
	v.clear();
}

void GameState::resetBool(bool& b, bool value)
{
	b = value;
}

void GameState::resetCounter(int& i)
{
	i = 0;
}
