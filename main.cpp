#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <Windows.h>

using namespace std;
using namespace sf;

//to declare a winner: change the symbols in winning fields to a thumb-up or something, one by one
//should have room below for messages

void initGrid(char grid[3][3]);
void initCoordinates(Vector2f coordinates[3][3]);
bool gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningIndices);
void switchPlayer(char& currentPlayer);

int main()
{
	//TO DO: Add room for system messages below board
	RenderWindow window(VideoMode(900, 900), "Tic-Tac-Toe", Style::Close);

	Texture boardTexture;
	boardTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Textures/ttt_board.png");
	Sprite boardSprite(boardTexture);

	Texture oTexture;
	oTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Textures/o.png");
	Sprite oSprite(oTexture);


	Texture xTexture;
	xTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Textures/x.png");
	Sprite xSprite(xTexture);

	Texture thumbUpTexture;
	thumbUpTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Textures/thumb_up.png");
	Sprite thumbUpSprite(thumbUpTexture);

	Texture plainWhiteTexture;
	plainWhiteTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Textures/white_bg.png");
	Sprite whiteBackground(plainWhiteTexture);

	char grid[3][3];
	initGrid(grid);

	Vector2f coordinates[3][3];
	initCoordinates(coordinates);

	char currentPlayer = 'x';
	Vector2i currentIndices = Vector2i(0, 0);

	bool isGameOver = false;
	bool winSequenceOver = false;

	vector<Vector2i> winningIndices {};
	winningIndices.reserve(3);

	int counter = 0;
	int subCounter = 0;

	//main loop > TO DO: refactor into a function
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Button::Left)
				{
					if (isGameOver) break;

					Vector2i position = Mouse::getPosition(window);
					currentIndices = Vector2i(position.x / 300, position.y / 300);

					if (currentIndices.x <= 2 && currentIndices.y <= 2 &&
						currentIndices.x >= 0 && currentIndices.y >= 0 &&
						grid[currentIndices.x][currentIndices.y] == ' ')
					{
						grid[currentIndices.x][currentIndices.y] = currentPlayer;

						if (gameOver(grid, currentPlayer, winningIndices))
						{
							cout << "Press RMB to restart." << endl;
							isGameOver = true;
						}

						switchPlayer(currentPlayer);
					}
				}

				if (event.mouseButton.button == Mouse::Button::Right)
				{
					initGrid(grid);
					winningIndices.clear();
					isGameOver = false;
					winSequenceOver = false;
				}
			}

			if (event.type == Event::Closed)
				window.close();
		}

		//draw board
		window.draw(boardSprite);

		//draw x and o

		if (!isGameOver || winSequenceOver)
		{
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					if (grid[i][j] == ' ')
						continue;

					Sprite thisSprite;

					if (grid[i][j] == 'x')
						thisSprite = xSprite;
					else if (grid[i][j] == 'o')
						thisSprite = oSprite;
					else if (grid[i][j] == 'w')
						thisSprite = thumbUpSprite;

					thisSprite.setPosition(Vector2f(coordinates[i][j]));
					window.draw(thisSprite);
				}

			}

			window.display();
		}
		
		
		if (!winSequenceOver && isGameOver)
		{
			for (size_t i = 0; i < 3; i++)
			{
				for (size_t j = 0; j < 3; j++)
				{
					if (grid[i][j] == ' ')
						continue;

					Sprite thisSprite;

					if (grid[i][j] == 'x')
						thisSprite = xSprite;
					else if (grid[i][j] == 'o')
						thisSprite = oSprite;

					thisSprite.setPosition(Vector2f(coordinates[i][j]));
					window.draw(thisSprite);
				}

			}

			Sleep(200);

			Sprite whitebg = whiteBackground;
			Sprite winSprite = thumbUpSprite;

			int x = winningIndices.at(subCounter).x;
			int y = winningIndices.at(subCounter).y;

			whitebg.setPosition(Vector2f(coordinates[x][y]));
			winSprite.setPosition(Vector2f(coordinates[x][y]));

			window.draw(whitebg);
			window.draw(winSprite);

			if (subCounter != 2)
				subCounter++;
			else
				subCounter = 0;

			counter++;

			if (counter == 10)
			{
				for (size_t i = 0; i < 3; i++)
				{
					int x = winningIndices.at(i).x;
					int y = winningIndices.at(i).y;

					grid[x][y] = 'w';
				}

				winSequenceOver = true;
			}
			
			window.display();
		}



		//if (!winSequenceOver && isGameOver)
		//{
		//	for (size_t i = 0; i < 3; i++)
		//	{
		//		int x = winningIndices.at(i).x;
		//		int y = winningIndices.at(i).y;

		//		grid[x][y] = 'w';
		//	}

		//	int counter = 0;

		//	Sleep(500);

		//	while (counter < 3)
		//	{
		//		for (size_t i = 0; i < 3; i++)
		//		{
		//			//Sprite whitebg = whiteBackground;
		//			Sprite winSprite = thumbUpSprite;

		//			int x = winningIndices.at(i).x;
		//			int y = winningIndices.at(i).y;

		//			//whitebg.setPosition(Vector2f(coordinates[x][y]));
		//			winSprite.setPosition(Vector2f(coordinates[x][y]));

		//			//window.draw(whitebg);
		//			window.draw(winSprite);
		//			window.display();

		//			Sleep(500);

		//			//whitebg.setColor(Color::Transparent);
		//			winSprite.setColor(Color::Transparent);					
		//		}

		//		counter++;

		//	}

		//	winSequenceOver = true;
		//}
	}
}

void initGrid(char grid[3][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			grid[i][j] = ' ';
		}
	}
}

void initCoordinates(Vector2f coordinates[3][3])
{
	for (size_t i = 0; i < 3; i++)
	{
		float incrementY = i * 300;

		for (size_t j = 0; j < 3; j++)
		{
			float incrementX = j * 300;

			coordinates[j][i] = Vector2f(incrementX, incrementY);
			cout << "Coordinate: " << coordinates[j][i].x << ", " << coordinates[j][i].y << endl;
		}
	}
}

void switchPlayer(char& currentPlayer)
{
	currentPlayer == 'x' ? currentPlayer = 'o' : currentPlayer = 'x';
}

bool gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningIndices)
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
