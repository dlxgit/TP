#pragma once
#include "game.h"
#include "snake.h"
#include "map.h"

using namespace sf;

struct Apple
{
	Vector2i pos;
	Texture texture;
	Sprite sprite;
};

void SpawnNewApple(Snake * snake, Apple * apple);

void CheckEventApple(Snake * snake, Apple * apple);

void InitializeApple(Apple * apple, Snake * snake);

void DrawApple(RenderWindow & window, Apple * apple);
