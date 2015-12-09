#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


const int N_BLOCKS = 5;  //quantity of blocks
const int RIGHT_X = 580;
const int DOWN_Y = 370;

struct Block
{
	RectangleShape shape;
	Vector2f startPos;
};

void InitializeBlocks(vector<Block> & blocks);

void ChangeColor(vector<Block> & blocks, int number);

void Draw(RenderWindow & window, vector<Block> & blocks);
