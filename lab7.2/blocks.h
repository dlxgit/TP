#pragma once
#include <SFML/Graphics.hpp>
#include "constants.h"

using namespace sf;
using namespace std;



struct Block
{
	RectangleShape shape;
	Vector2f startPos;
};

void InitializeBlocks(vector<Block> & blocks);

void ChangeColor(vector<Block> & blocks, int number);

void Draw(RenderWindow & window, vector<Block> & blocks);
