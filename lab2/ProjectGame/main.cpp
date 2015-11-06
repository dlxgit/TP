#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "map.h"

using namespace sf;

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE,
};

enum State
{
	BEGIN,
	CONTINUE,
	END
};

const int TIME_STEP = 200;	// gameSpeed(milliSeconds)

Vector2i SnakeParts[(WIDTH / STEP) * (HEIGHT / STEP)]; //array of max_number of blocks on map

void Tick(int & snakeSize)
{
	for (int i = snakeSize - 1; i > 0; --i)
	{
		SnakeParts[i].x = SnakeParts[i - 1].x;
		SnakeParts[i].y = SnakeParts[i - 1].y;
	}
	if (SnakeParts[snakeSize - 1].x == SnakeParts[snakeSize].x || SnakeParts[snakeSize - 1].y == SnakeParts[snakeSize].y)
		snakeSize += 1;
}

void AddNewSnakePart(int & snakeSize)
{
	SnakeParts[snakeSize].x = SnakeParts[snakeSize - 1].x;
	SnakeParts[snakeSize].y = SnakeParts[snakeSize - 1].y;
}

void SpawnNewApple(Sprite & appleSprite, int & snakeSize)
{
	int x;
	int y;
	bool isPlaceFound = true;

	do
	{
		x = (rand() % WIDTH / STEP);
		y = (rand() % HEIGHT / STEP);
		isPlaceFound = true;

		if (TILEMAP[y][x] == 'b')
		{
			isPlaceFound = false;
		}
		else
			for (int i = 0; i < snakeSize; i++)
				if (SnakeParts[i].x == x && SnakeParts[i].y == y)
				{
					isPlaceFound = false;
					break;
				}

	} while (isPlaceFound == false);
	appleSprite.setPosition(x * STEP, y * STEP);
}

void CheckEventApple(Sprite & appleSprite, int & snakeSize)
{
	int x_apple;
	int y_apple;

	x_apple = appleSprite.getPosition().x;
	y_apple = appleSprite.getPosition().y;

	if (x_apple == (SnakeParts[0].x * STEP) && y_apple == (SnakeParts[0].y * STEP))
	{
		SpawnNewApple(appleSprite, snakeSize);
	}
	if (x_apple == (SnakeParts[0].x * STEP) && y_apple == (SnakeParts[0].y * STEP))
	{
		AddNewSnakePart(snakeSize);
	}
}

void Update(Direction & dir)
{
	switch (dir)
	{
	case UP:
		SnakeParts[0].y -= 1;
		break;
	case DOWN:
		SnakeParts[0].y += 1;
		break;
	case LEFT:
		SnakeParts[0].x -= 1;
		break;
	case RIGHT:
		SnakeParts[0].x += 1;
		break;
	case NONE:
		break;
	}
}


void CheckGameOver(int & snakeSize, State & gameState)
{
	if (TILEMAP[SnakeParts[0].y][SnakeParts[0].x] == 'b')
	{
		gameState = END;
	}
	else
		for (int i = 1; i < snakeSize; i++)
			if (SnakeParts[0].x == SnakeParts[i].x && SnakeParts[0].y == SnakeParts[i].y)
			{
				gameState = END;
				break;
			}
}

void ProcessEvents(RenderWindow & window, Direction & dir, Direction & dirPast)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && dirPast != RIGHT)
		{
			dir = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && dirPast != LEFT)
		{
			dir = RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && dirPast != DOWN)
		{
			dir = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && dirPast != UP)
		{
			dir = DOWN;
		}
		if (event.type == Event::Closed)
			window.close();
	}
}

void ResetDefaultVariables(int & snakeSize, Direction & dir)  //for restart
{
	for (int i = 1; i < snakeSize; i++)
	{
		SnakeParts[i].x = 0;
		SnakeParts[i].y = 0;
	}
	snakeSize = 1;
	SnakeParts[0].x = 9; //snakeHead
	SnakeParts[0].y = 7; //snakeHead
	dir = NONE;
}

void BeginEvent(Text & text, RenderWindow & window, State & state, int & snakeSize, Direction & dir)
{
	text.setString("Press Enter to play");
	text.setPosition(180, 220);
	window.draw(text);

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		ResetDefaultVariables(snakeSize, dir);
		state = CONTINUE;
	}
}

void EndGameEvent(Text & text, RenderWindow & window, State & state, int & snakeSize, Direction & dir) //messages
{
	text.setString("GAME OVER");
	text.setPosition(230, 180);
	window.draw(text);

	std::ostringstream playerScoreString;
	playerScoreString << (snakeSize - 1) * 10;
	text.setString("SCORE: " + playerScoreString.str());
	text.setPosition(240, 250);
	window.draw(text);

	text.setString("Press Enter to restart");
	text.setPosition(160, 350);
	window.draw(text);

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		ResetDefaultVariables(snakeSize, dir);
		state = CONTINUE;
	}
}

void DrawField(Sprite & fieldSprite, RenderWindow & window)
{
	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 20; j++)
		{
			if (TILEMAP[i][j] == ' ')
			{
				fieldSprite.setTextureRect(IntRect(0, 0, 32, 32));
			}
			else if (TILEMAP[i][j] == 'b')
			{
				fieldSprite.setTextureRect(IntRect(32, 0, 32, 32));
			}

			fieldSprite.setPosition(j * STEP, i * STEP);
			window.draw(fieldSprite);
		}
}

void DrawApple(Sprite & apple_block, RenderWindow & window)
{
	window.draw(apple_block);
}

void DrawSnake(Sprite & snakeSprite, int & snakeSize, RenderWindow & window)
{
	for (int i = 0; i < snakeSize; i++)
	{
		snakeSprite.setPosition(SnakeParts[i].x * STEP, SnakeParts[i].y * STEP);
		window.draw(snakeSprite);
	}
}

void main()
{
	//loading sprites(field,snake,apple,block)
	Texture textureField;
	textureField.loadFromFile("texture.png");
	Sprite fieldSprite;
	fieldSprite.setTexture(textureField);
	Sprite snakeSprite;
	snakeSprite.setTexture(textureField);
	snakeSprite.setTextureRect(IntRect(64, 0, 32, 32));
	Sprite appleSprite;
	appleSprite.setTexture(textureField);
	appleSprite.setTextureRect(IntRect(96, 0, 32, 32));

	//text
	Font font;
	font.loadFromFile("Arialbd.ttf");
	Text text("", font, 30);
	text.setColor(Color::Red);

	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake");

	Clock clock;
	int time = 0;
	State state = BEGIN;
	Direction dir = NONE;
	Direction dirPast = NONE;
	int snakeSize = 1; //size of snake


	//setFirstApple
	SpawnNewApple(appleSprite, snakeSize);

	while (window.isOpen())
	{
		window.clear();

		//checkWindowClose
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		switch (state)
		{
		case BEGIN:
			BeginEvent(text, window, state, snakeSize, dir);
			break;
		case END:
			EndGameEvent(text, window, state, snakeSize, dir);
			break;
		case CONTINUE:
			time = 0; //обнуляем время
			while (time < TIME_STEP) //пока время не достигнет нужного значения, ничего на экране не изменится
			{
				ProcessEvents(window, dir, dirPast);
				time = clock.getElapsedTime().asMilliseconds(); //время в милисекундах
			}

			if (time >= TIME_STEP)
			{
				clock.restart();   //перезагружает время

				dirPast = dir;

				ProcessEvents(window, dir, dirPast);             //определяем направление змейки
				Tick(snakeSize);
				Update(dir);                          //обновляем координаты головы змейки
				CheckEventApple(appleSprite, snakeSize);      //проверка поедания яблока
				CheckGameOver(snakeSize, state);                   //проверка на конец игры

				DrawField(fieldSprite, window);    //рисуем карту
				DrawSnake(snakeSprite, snakeSize, window);    //рисуем змейку      
				DrawApple(appleSprite, window);    //рисуем яблоко
			}
			break;
		}
		window.display();
	}
}