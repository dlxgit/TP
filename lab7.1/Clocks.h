#pragma once

#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "hands.h"

#define M_PI 3.14159265

using namespace sf;

const Vector2f CLOCK_CENTER{ float(200), float(200) };
const int CIRCLE_RADIUS = 170;
const Vector2f CIRCLE_POS = { CLOCK_CENTER.x - CIRCLE_RADIUS, CLOCK_CENTER.y - CIRCLE_RADIUS };

struct Clocks
{
	CircleShape circle;
	CircleShape centerCircle;
	RectangleShape markers[12];
	Vector2f pos;
};

void InitializeMarkers(RectangleShape * markers);

void InitializeClocks(Clocks & clocks);

void DrawMarkers(RenderWindow & window, RectangleShape(&markers)[12]);

void Draw(RenderWindow & window, Clocks & clocks, Hands & hands);
