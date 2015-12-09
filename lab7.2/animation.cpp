#include "animation.h"

void Animation5(vector<Block> & blocks, int & stateIndex)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		Vector2f pos = blocks[i].shape.getPosition();
		pos.y -= 3;
		blocks[i].shape.setPosition(pos);
	}
	if (blocks[0].shape.getPosition().y <= blocks[0].startPos.y)
	{
		ChangeColor(blocks, 1);
		stateIndex = 1;
	}
}

void Animation4(vector<Block> & blocks, int & stateIndex)
{
	float yMax = blocks[N_BLOCKS - 1].shape.getPosition().y;
	for (int i = 0; i < N_BLOCKS; i++)
	{
		Vector2f pos = blocks[i].shape.getPosition();
		pos.x += ((blocks[i].startPos.x - blocks[i].shape.getPosition().x) / ((yMax - blocks[0].shape.getPosition().y) / float(2)));
		pos.y += ((yMax - blocks[i].shape.getPosition().y) / ((yMax - blocks[0].shape.getPosition().y) / float(2)));
		blocks[i].shape.setPosition(pos);
		if (blocks[0].shape.getPosition().y >= yMax)
		{
			ChangeColor(blocks, 5);
			stateIndex++;
			break;
		}
	}
}

void Animation3(vector<Block> & blocks, int & stateIndex)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		Vector2f pos = blocks[i].shape.getPosition();
		pos.x -= float(2);
		blocks[i].shape.setPosition(pos);

		if (blocks[i].shape.getRotation() < 700)
		{
			if (!(blocks[i].shape.getPosition().x < 100 && blocks[i].shape.getRotation() == 0))
			{
				blocks[i].shape.rotate(5);
			}
			if (blocks[i].shape.getScale().x > 1)
			{
				blocks[i].shape.setScale(blocks[i].shape.getScale().x - 0.005, blocks[i].shape.getScale().y - 0.001);
			}
		}
	}
	if (blocks[0].shape.getPosition().x <= blocks[0].startPos.x)
	{
		ChangeColor(blocks, 4);
		stateIndex++;
	}
}

void Animation2(vector<Block> & blocks, int & stateIndex)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		Vector2f pos = blocks[i].shape.getPosition();

		if (blocks[i].shape.getScale().x < 1.9)
		{
			blocks[i].shape.setScale(blocks[i].shape.getScale().x + 0.005, blocks[i].shape.getScale().y + 0.001);
		}
		if (blocks[i].shape.getRotation() < 90)
		{
			blocks[i].shape.rotate(2);
		}

		if (pos.x < RIGHT_X)
		{
			pos.x += ((float(RIGHT_X) - blocks[i].shape.getPosition().x) / ((float(RIGHT_X) - blocks[N_BLOCKS - 1].shape.getPosition().x) / float(2)));
			blocks[i].shape.setPosition(pos);
		}
	}
	if (blocks[0].shape.getPosition().x >= RIGHT_X)
	{
		ChangeColor(blocks, 3);
		stateIndex++;
	}
}

void Animation1(vector<Block> & blocks, int & stateIndex)
{
	for (int i = 0; i < N_BLOCKS; i++)
	{
		Vector2f pos = blocks[i].shape.getPosition();
		pos.y += 1 * i + 1;
		blocks[i].shape.setPosition(pos);
	}
	if (blocks[N_BLOCKS - 1].shape.getPosition().y > DOWN_Y)
	{
		ChangeColor(blocks, 2);
		stateIndex++;
	}
}

void Update(vector<Block> & blocks, int & stateIndex)
{
	switch (stateIndex)
	{
	case 1:
		Animation1(blocks, stateIndex);
		break;
	case 2:
		Animation2(blocks, stateIndex);
		break;
	case 3:
		Animation3(blocks, stateIndex);
		break;
	case 4:
		Animation4(blocks, stateIndex);
		break;
	case 5:
		Animation5(blocks, stateIndex);
		break;
	}
}
