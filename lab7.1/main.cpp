#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <cmath>
#include "hands.h"
#include "clocks.h"

using namespace sf;

void CheckWindowClose(RenderWindow & window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			window.close();
		}
	}
}

void main()
{
	Clocks clocks;
	Hands hands;
	InitializeHands(hands);
	InitializeClocks(clocks);

	sf::ContextSettings settings;  //initialization of window
	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(400, 400), "Clock", sf::Style::Default, settings);

	Clock frameClock;   //time for screen-update
	float timeSinceLastFrame;

	while (window.isOpen())
	{
		timeSinceLastFrame = frameClock.getElapsedTime().asSeconds();
		CheckWindowClose(window);
		if (timeSinceLastFrame >= 1)		//screen update every second
		{
			window.clear(Color::White);
			frameClock.restart();

			UpdateClockTime(hands);
			ComputeHandsPosition(hands); 
			Draw(window, clocks, hands);

			window.display();
		}
	}
}