#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

const int WIDTH_BASIC = 640;
const int HEIGHT_BASIC = 480;

enum State
{
	SHOW_IMAGE,
	INVALID_DIR,
	EMPTY_DIR,
	UNABLE_TO_LOAD
};

struct Settings
{
	int index;
	bool isButtonPressed;
	Vector2f mouseDrag;
	Vector2f mouseLastPos;
	int zoom;
	Texture texture;
	Sprite sprite;
	Vector2f windowSize;
	Vector2f imageSize;
	Vector2f scale;
	char names[100][50];
	int nFiles;
	bool isChanged;
	State state;
};

struct Buttons
{
	Texture textureButtons;
	Texture textureZoom;
	Sprite left;
	Sprite right;
	Sprite plus;
	Sprite minus;
};