#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace sf;

const static float CAR_WIDTH = 244.f;
const static float ACCELERATION = 0.05f;
const static Vector2f WINDOW_SIZE = { 800.f,600.f };
const static int TIME_PER_FRAME = 15;  //in milliseconds

const static Vector2f BACK_WHEEL_POS = { 54.f,72.f };
const static float WHEEL_DISTANCE = 144.f;
const static Vector2f START_POS = { 0,250.f };


struct Physics
{
	float rotation;
	float speed;
	Vector2f carPos;
	float slowingPos;
};


void InitializePhysics(Physics & physics);

void ComputePhysics(Physics & physics);
