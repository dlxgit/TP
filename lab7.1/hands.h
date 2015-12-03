#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>

using namespace sf;


struct Hand
{
	RectangleShape line;
	Vector2f pos;
	float time;
	float maxTime;
	float angle;
};

struct Hands
{
	Hand second;
	Hand minute;
	Hand hour;
};


void InitializeHands(Hands & hands);

void ComputeHandsPosition(Hands & hands);

void UpdateClockTime(Hands & hands);

void DrawHands(RenderWindow & window, Hands & hands);
