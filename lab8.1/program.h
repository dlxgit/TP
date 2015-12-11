#pragma once
#include "car.h"

void ProcessEvents(RenderWindow & window);

void Draw(RenderWindow & window, Car & car, const RectangleShape & ground);

void StartProgram(RenderWindow & window, Car & car, Physics & physics, const RectangleShape & ground);