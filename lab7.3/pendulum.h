#pragma once
#include "constants.h"

struct Wheel
{
	Texture texture;
	Sprite sprite;
	float rotation;
};

struct Pendulum
{
	Pendulum() {};
	ConvexShape weight;
	ConvexShape turn;
	float rotation;
	float speed;
	Wheel firstWheel;
	Wheel secondWheel;
};

void InitializePendulum(Pendulum & pendulum);

void UpdatePendulum(Pendulum & pendulum);

void ComputePhysics(Pendulum & pendulum);

void Draw(RenderWindow & window, Pendulum & pendulum);