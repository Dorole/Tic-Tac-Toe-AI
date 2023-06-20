#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

//to declare a winner: change the symbols in winning fields to a thumb-up or something, one by one
//should have room below for messages

void initGrid(char grid[3][3]);
void initCoordinates(Vector2f coordinates[3][3]);
bool gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningCoordinates);
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

	char grid[3][3];
	initGrid(grid);

	Vector2f coordinates[3][3];
	initCoordinates(coordinates);

	char currentPlayer = 'x';
	Vector2i currentIndices = Vector2i(0, 0);

	bool allowSymbolInput = true;

	vector<Vector2i> winningCoordinates {};
	winningCoordinates.reserve(30);

	//debug
	winningCoordinates.push_back(Vector2i(0, 0));
	winningCoordinates.push_back(Vector2i(0, 0));
	winningCoordinates.push_back(Vector2i(0, 0));

	for (size_t i = 0; i < winningCoordinates.size(); i++)
	{
		cout << "Win coord: " << winningCoordinates.at(i).x << ", " << winningCoordinates.at(i).y << endl;
	}


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
					if (!allowSymbolInput) break;

					Vector2i position = Mouse::getPosition(window);
					//cout << "X: " << position.x << endl;
					//cout << "Y: " << position.y << endl;
					cout << "COORDINATES: " << position.x / 300 << ", " << position.y / 300 << endl;

					currentIndices = Vector2i(position.x / 300, position.y / 300);
					//cout << "Current indices: " << currentIndices.x << ", " << currentIndices.y << endl;
					//cout << "Current coordinates: " << coordinates[currentIndices.x][currentIndices.y].x << ", " << coordinates[currentIndices.x][currentIndices.y].y << endl;

					if (currentIndices.x <= 2 && currentIndices.y <= 2 &&
						currentIndices.x >= 0 && currentIndices.y >= 0 &&
						grid[currentIndices.x][currentIndices.y] == ' ')
					{
						grid[currentIndices.x][currentIndices.y] = currentPlayer;

						//this check shouldn't be here? (only input checks?)
						if (gameOver(grid, currentPlayer, winningCoordinates))
						{
							cout << "Press RMB to restart." << endl;
							allowSymbolInput = false;

							//debug
							cout << "WIN COORDINATE 0: " << winningCoordinates.at(0).x << ", " << winningCoordinates.at(0).y << endl;
						}

						switchPlayer(currentPlayer);
					}
				}

				//debug restart
				if (event.mouseButton.button == Mouse::Button::Right)
				{
					initGrid(grid);
					allowSymbolInput = true;
				}
			}

			if (event.type == Event::Closed)
				window.close();
		}

		//draw board
		window.draw(boardSprite);

		//draw x and o
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

		window.display();

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

bool gameOver(char grid[3][3], char currentPlayer, vector<Vector2i>& winningCoordinates)
{
	//check rows
	for (int i = 0; i < 3; i++)
	{
		if (grid[i][0] != ' ' && grid[i][0] == currentPlayer && (grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2]))
		{
			cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;
			
			//debug
			winningCoordinates.clear();
			winningCoordinates.at(0).x = 7;
			winningCoordinates.at(0).y = 9;
			winningCoordinates.push_back(Vector2i(7, 9));

			return true;
		}
	}

	//check columns
	for (int j = 0; j < 3; j++)
	{
		if (grid[0][j] != ' ' && grid[0][j] == currentPlayer && (grid[0][j] == grid[1][j] && grid[1][j] == grid[2][j]))
		{
			cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;
			return true;
		}
	}

	//check diagonals
	if (grid[1][1] != ' ' && grid[1][1] == currentPlayer &&
		((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2]) ||
			(grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])))
	{
		cout << "\n********** The winner is " << currentPlayer << "! **********" << endl;
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

