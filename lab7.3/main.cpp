#include <SFML/Graphics.hpp>
#include "program.h"

void main()
{
	Pendulum pendulum;
	InitializePendulum(pendulum);

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "lab 7.3", sf::Style::Default, settings);

	StartProgram(window, pendulum);
}