#pragma once
#include "physics.h"

struct Wheel
{
	Texture texture;
	Sprite sprite;
};

struct Car
{
	Texture texture;
	Sprite sprite;
	float width;
	Wheel frontWheel;
	Wheel backWheel;
};

void InitializeCar(Car & car);

void UpdateCar(Car & car, Physics & physics);
