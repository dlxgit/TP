#include "apple.h"

void SpawnNewApple(Snake * snake, Apple * apple)
{
	Vector2i place;
	bool isPlaceFound;
	isPlaceFound = true;

	do
	{
		place.x = (rand() % (WIDTH / STEP));
		place.y = (rand() % (HEIGHT / STEP));
		isPlaceFound = true;

		if (TILEMAP[place.y][place.x] == 'b')
		{
			isPlaceFound = false;
		}

		else
			for (int i = 0; i != snake->parts.size(); i++)
				if (snake->parts[i].x == (place.x * STEP) && snake->parts[i].y == (place.y * STEP))
				{
					isPlaceFound = false;
					break;
				}

	} while (isPlaceFound == false);

	apple->pos = { place.x * STEP, place.y * STEP };

	apple->sprite.setPosition(float(place.x * STEP), float(place.y * STEP));
};

void CheckEventApple(Snake * snake, Apple * apple)
{
	Vector2i posApple;

	posApple.x = int(apple->sprite.getPosition().x);
	posApple.y = int(apple->sprite.getPosition().y);

	Vector2i head;
	head = snake->parts[0];
	if (head == posApple)
	{
		SpawnNewApple(snake, apple);
		AddNewSnakePart(snake);
	}
};

void InitializeApple(Apple * apple, Snake * snake)
{
	apple->texture.loadFromFile("resource/texture.png");
	apple->sprite.setTexture(apple->texture);
	apple->sprite.setTextureRect(IntRect(96, 0, 32, 32));
	SpawnNewApple(snake, apple);
}

void DrawApple(RenderWindow & window, Apple * apple)
{
	window.draw(apple->sprite);
};