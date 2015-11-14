#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const static int TIME_STEP = 200;	// gameSpeed(milliSeconds)

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

void InitializeGame(Game * &game);

void DrawField(RenderWindow & window, Game * game);

