#include <SFML/Graphics.hpp>
#include "program.h"

void main()
{
	Car car;
	Physics physics;
	InitializeCar(car);
	InitializePhysics(physics);
	RenderWindow window(sf::VideoMode(WINDOW_SIZE.x,WINDOW_SIZE.y), "lab 8.1");

	RectangleShape ground(Vector2f(WINDOW_SIZE.x, 330));
	ground.setFillColor(Color(90,103,39));
	ground.setPosition(0, 344);

	StartProgram(window, car, physics,ground);
}