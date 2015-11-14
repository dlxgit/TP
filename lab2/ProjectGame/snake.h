#pragma once
#include "map.h"
#include "game.h"
#include <vector>
#include <sstream>

using namespace sf;
using namespace std;

struct Snake
{
	int size;
	vector<Vector2i> parts;
	Direction dir;
	Direction dirPast;
	Texture texture;
	Sprite sprite;
};

void Tick(Snake * snake);

void AddNewSnakePart(Snake * snake);

void Update(Snake * snake);

void InitializeSnake(Snake * snake);

void ProcessEvents(RenderWindow & window, Snake * snake);

void DrawSnake(RenderWindow & window, Snake * snake);

void ResetSnake(Snake * snake);  //for restart

void BeginEvent(RenderWindow & window, Game * game, Snake * snake);

void EndGameEvent(RenderWindow & window, Game * game, Snake * snake);

void CheckGameOver(Game * game, Snake * snake);

