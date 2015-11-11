#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int TIME_STEP = 200;	// gameSpeed(milliSeconds)

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

struct Game
{
	State state;
	Font font;
	Text text;
	float time;
	Texture texture;
	Sprite fieldSprite;
	Sprite blockSprite;
};

void InitializeGame(Game * &game)
{
	//game = new Game();
	game->state = BEGIN;
	game->time = 0;

	game->font.loadFromFile("resource/Font.ttf");
	Text text("", game->font, 30);
	text.setColor(Color::Red);
	game->text = text;

	game->texture.loadFromFile("resource/texture.png");
	game->fieldSprite.setTexture(game->texture);
	game->blockSprite.setTexture(game->texture);
	game->fieldSprite.setTextureRect(IntRect(0, 0, 32, 32));
	game->blockSprite.setTextureRect(IntRect(32, 0, 32, 32));
	//time
}
