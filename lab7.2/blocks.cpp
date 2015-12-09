#include "blocks.h"

void InitializeBlocks(vector<Block> & blocks)
{
	Block block;

	for (int i = 0; i < N_BLOCKS; i++)
	{
		block.shape.setFillColor(Color::Green);
		block.shape.setSize(Vector2f(float(40), float(20)));
		block.startPos = { float(60 * i + 30), float(10) };
		block.shape.setPosition(block.startPos);
		blocks.push_back(block);
	}
}

void ChangeColor(vector<Block> & blocks, int number)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		switch (number)
		{
		case 1:
			blocks[i].shape.setFillColor(Color::Green);
			break;
		case 2:
			blocks[i].shape.setFillColor(Color(139, 69, 19));
			break;
		case 3:
			blocks[i].shape.setFillColor(Color::Red);
			break;
		case 4:
			blocks[i].shape.setFillColor(Color::Blue);
			break;
		case 5:
			blocks[i].shape.setFillColor(Color::Yellow);
			break;
		}
	}
}

void Draw(RenderWindow & window, vector<Block> & blocks)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		window.draw(blocks[i].shape);
	}
}