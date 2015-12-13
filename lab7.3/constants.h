#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include <SFML/Graphics.hpp>

using namespace sf;

const static float ACCELERATION = 0.02f;
const static Vector2i WINDOW_SIZE = { 1000,600 };
const static int TIME_PER_FRAME = 15;  //in milliseconds

const static Vector2f PENDULUM_POS = { 650,170 };
const static Vector2f FIRST_WHEEL_POS = {140,303};
const static Vector2f SECOND_WHEEL_POS = {370,200};
const static float START_ROTATION = -60.f;