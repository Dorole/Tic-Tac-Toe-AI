#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <string>
#include <Windows.h>

#include "TextMessages.h"
#include "SoundPlayer.h"
#include "GameState.h"


using namespace std;
using namespace sf;


int main()
{
	TextMessages textMessages;
	SoundPlayer soundPlayer;
	GameState gameState;

	RenderWindow window(VideoMode(900, 1100), "Tic-Tac-Toe", Style::Close);

	// **************** TEXTURES ****************
	Texture boardTexture;
	boardTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/board_v2.png");
	Sprite boardSprite(boardTexture);

	Texture oTexture;
	oTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/o.png");
	Sprite oSprite(oTexture);


	Texture xTexture;
	xTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/x.png");
	Sprite xSprite(xTexture);

	Texture thumbUpTexture;
	thumbUpTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/thumb_up.png");
	Sprite thumbUpSprite(thumbUpTexture);

	Texture plainWhiteTexture;
	plainWhiteTexture.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/white_bg.png");
	Sprite whiteBackground(plainWhiteTexture);

	// **************** TEXT ****************

	Font font;
	font.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/AnagramShadowNF.ttf");
	Text message;
	message.setFont(font);
	message.setCharacterSize(80);

	Vector2f startTextPosition = Vector2f(280, 940);
	Vector2f winTextPosition = Vector2f(300, 940);
	Color xTextColor = Color(63, 133, 164);
	Color oTextColor = Color(213, 77, 221);

	Text xScoreText;
	xScoreText.setFont(font);
	xScoreText.setCharacterSize(100);
	xScoreText.setPosition(Vector2f(60, 930));
	xScoreText.setFillColor(xTextColor);

	Text oScoreText;
	oScoreText.setFont(font);
	oScoreText.setCharacterSize(100);
	oScoreText.setPosition(Vector2f(770, 930));
	oScoreText.setFillColor(oTextColor);

	// **************** AUDIO ****************

	SoundBuffer buffer;
	buffer.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/plop1.flac");
	Sound clickSound_one(buffer);

	SoundBuffer bufferTwo;
	bufferTwo.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/plop2.wav");
	Sound clickSound_two(bufferTwo);

	vector<Sound> sounds {clickSound_one, clickSound_two};

	SoundBuffer restartBuffer;
	restartBuffer.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/restart.flac");
	Sound restartSound(restartBuffer);

	SoundBuffer winBuffer;
	winBuffer.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/win.wav");
	Sound winSound(winBuffer);

	SoundBuffer tieBuffer;
	tieBuffer.loadFromFile("C:/Users/dorot/Desktop/C++/Tic-Tac-Toe-AI/Resources/tie.wav");
	Sound tieSound(tieBuffer);

	// **************** GAME VARIABLES ****************

	char grid[3][3];
	gameState.initGrid(grid);

	Vector2f coordinates[3][3];
	gameState.initCoordinates(coordinates);

	char currentPlayer = 'x';
	Vector2i currentIndices = Vector2i(0, 0);

	//ovo u neki state machine?
	bool newSession = true;
	bool isGameOver = false;
	bool winSequenceOver = false;

	vector<Vector2i> winningIndices {};
	winningIndices.reserve(3);

	int counter = 0;
	int subCounter = 0;

	int xScore = 0;
	int oScore = 0;

	// ************************************** GAME WINDOW **************************************

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::EventType::MouseButtonPressed)
			{
				//if valid field selected, set the field to current player's symbol
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

						if (newSession)
						{
							newSession = false;
						}

						if (gameState.gameOver(grid, currentPlayer, winningIndices))
						{
							cout << "Press RMB to restart." << endl;
							isGameOver = true;

							if (winningIndices.size() > 1)
							{
								currentPlayer == 'x' ? xScore++ : oScore++;
								winSound.play();
							}
							else
							{
								tieSound.play();
							}
						}

						if (!isGameOver)
							gameState.switchPlayer(currentPlayer);
					}

					soundPlayer.playRandomSound(sounds);
				}

				//reset session
				if (event.mouseButton.button == Mouse::Button::Right)
				{
					gameState.initGrid(grid);
					gameState.resetVector(winningIndices);
					gameState.resetBool(isGameOver, false);
					gameState.resetBool(winSequenceOver, false);
					gameState.resetBool(newSession, true);
					gameState.resetCounter(counter);
					gameState.resetCounter(subCounter);

					gameState.switchPlayer(currentPlayer);

					restartSound.play();
				}
			}

			if (event.type == Event::Closed)
				window.close();
		}

		//draw board
		window.draw(boardSprite);

		//draw messages
		if (newSession || isGameOver)
		{
			if (newSession)
			{
				message.setString(textMessages.displayStartMessage(currentPlayer));
				message.setPosition(startTextPosition);
				message.setFillColor(textMessages.setTextColor(currentPlayer, xTextColor, oTextColor));
			}
			else if (isGameOver)
			{
				if (winningIndices.size() > 1)
				{
					message.setString(textMessages.displayWinMessage(currentPlayer));
					message.setPosition(winTextPosition);
					message.setFillColor(textMessages.setTextColor(currentPlayer, xTextColor, oTextColor));
				}
				else
				{
					message.setString("Tie!");
					message.setPosition(Vector2f(400,940));
					message.setFillColor(Color::Black);
				}
			}

		}
		else
		{
			message.setString("");
		}

		window.draw(message);

		xScoreText.setString(textMessages.displayCurrentScore(xScore));
		oScoreText.setString(textMessages.displayCurrentScore(oScore));
		window.draw(xScoreText);
		window.draw(oScoreText);

		//draw x and o (and thumb-up)
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

		//animate win screen
		if (isGameOver && !winSequenceOver && winningIndices.size() > 1)
		{
			Sleep(150);

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
		}

		window.display();

	}
}

