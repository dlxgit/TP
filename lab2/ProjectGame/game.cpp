#include "game.h"
#include "map.h"

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