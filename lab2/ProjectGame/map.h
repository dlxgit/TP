#pragma once
#include "game.h"

const int WIDTH = 640;
const int HEIGHT = 480;
const int STEP = 32;

const sf::String TILEMAP[HEIGHT / STEP] =
{
	"bbbbbbbbbbbbbbbbbbbb",
	"b                  b",
	"b                  b",
	"b   b   b  b   b   b",
	"b    b        b    b",
	"b        bb        b",
	"b                  b",
	"b bbbbb      bbbbb b",
	"b   b          b   b",
	"b      b    b      b",
	"b   b          b   b",
	"b bbbbb      bbbbb b",
	"b        bb        b",
	"b                  b",
	"bbbbbbbbbbbbbbbbbbbb",
};


void DrawField(RenderWindow & window, Game * game)
{
	for (int i = 0; i * STEP < HEIGHT; i += 1)
		for (int j = 0; j * STEP < WIDTH; j += 1)
		{
			if (TILEMAP[i][j] == ' ')
			{
				game->fieldSprite.setPosition(j * STEP, i * STEP);
				window.draw(game->fieldSprite);
			}
			else if (TILEMAP[i][j] == 'b')
			{
				game->blockSprite.setPosition(j * STEP, i * STEP);
				window.draw(game->blockSprite);
			}
		}
}
