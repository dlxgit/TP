#include "snake.h"

void Tick(Snake * snake)
{
	if (snake->size < snake->parts.size())
	{
		if (snake->parts[snake->size - 1] == snake->parts[snake->parts.size() - 1])
			snake->size += 1;
	}
	for (int i = snake->size - 1; i > 0; i--)
	{
		snake->parts[i] = snake->parts[i - 1];
	}
}

void AddNewSnakePart(Snake * snake)
{
	Vector2i part = snake->parts[snake->parts.size() - 1];
	snake->parts.push_back(part);
}

void Update(Snake * snake)
{
	switch (snake->dir)
	{
	case UP:
		snake->parts[0].y -= STEP;
		break;
	case DOWN:
		snake->parts[0].y += STEP;
		break;
	case LEFT:
		snake->parts[0].x -= STEP;
		break;
	case RIGHT:
		snake->parts[0].x += STEP;
		break;
	case NONE:
		break;
	}
	snake->dirPast = snake->dir;
}

void InitializeSnake(Snake * snake)
{
	snake->size = 1;
	Vector2i part;
	part = { 9 * STEP, 7 * STEP };
	snake->parts.push_back(part);
	snake->dir = NONE;
	snake->dirPast = NONE;
	snake->texture.loadFromFile("resource/texture.png");
	snake->sprite.setTexture(snake->texture);
	snake->sprite.setTextureRect(IntRect(64, 0, 32, 32));

}

void ProcessEvents(RenderWindow & window, Snake * snake)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (Keyboard::isKeyPressed(Keyboard::Left) && snake->dirPast != RIGHT)
		{
			snake->dir = LEFT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) && snake->dirPast != LEFT)
		{
			snake->dir = RIGHT;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up) && snake->dirPast != DOWN)
		{
			snake->dir = UP;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) && snake->dirPast != UP)
		{
			snake->dir = DOWN;
		}
		if (event.type == Event::Closed)
			window.close();
	}
}

void DrawSnake(RenderWindow & window, Snake * snake)
{
	for (int i = 0; i < snake->size; i++)
	{
		snake->sprite.setPosition(float(snake->parts[i].x), float(snake->parts[i].y));
		window.draw(snake->sprite);
	}
}

void ResetSnake(Snake * snake)  //for restart
{
	snake->parts.clear();
	snake->size = 1;

	Vector2i part;
	part.x = 9 * STEP; //snakeHead
	part.y = 7 * STEP; //snakeHead

	snake->parts.push_back(part);
	snake->dir = NONE;
	snake->dirPast = NONE;
}


void BeginEvent(RenderWindow & window, Game * game, Snake * snake)
{
	game->text.setString("Press Enter to play");
	game->text.setPosition(180, 220);
	window.draw(game->text);

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		ResetSnake(snake);
		game->state = CONTINUE;
	}
}


void CheckGameOver(Game * game, Snake * snake)
{
	if (TILEMAP[snake->parts[0].y / STEP][snake->parts[0].x / STEP] == 'b')
	{
		game->state = END;
	}
	else
		for (int i = 1; i < snake->size; i++)
			if (snake->parts[0] == snake->parts[i])
			{
				game->state = END;
				break;
			}
}

void EndGameEvent(RenderWindow & window, Game * game, Snake * snake)
{
	game->text.setString("GAME OVER");
	game->text.setPosition(230, 180);
	window.draw(game->text);

	std::ostringstream playerScoreString;
	playerScoreString << (snake->size - 1) * 10;
	game->text.setString("SCORE: " + playerScoreString.str());
	game->text.setPosition(240, 250);
	window.draw(game->text);

	game->text.setString("Press Enter to restart");
	game->text.setPosition(160, 350);
	window.draw(game->text);

	if (Keyboard::isKeyPressed(Keyboard::Return))
	{
		ResetSnake(snake);
		game->state = CONTINUE;
	}
}