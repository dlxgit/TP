#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "animation.h"

using namespace sf;
using namespace std;


void ProcessEvents(RenderWindow & window)
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

void StartProgram(RenderWindow & window, vector<Block> & blocks, int & stateIndex)
{
	Clock frameClock;   //time for screen-update
	float timeSinceLastFrame;

	while (window.isOpen())
	{
		timeSinceLastFrame = frameClock.getElapsedTime().asMilliseconds();
		ProcessEvents(window);
		if (timeSinceLastFrame >= 15)		//screen update every second
		{
			window.clear(Color::White);
			frameClock.restart();

			Update(blocks, stateIndex);
			Draw(window, blocks);

			window.display();
		}
	}
}

void main()
{
	vector<Block> blocks;
	InitializeBlocks(blocks);
	int stateIndex = 1;  //index of current state

	sf::ContextSettings settings;  //initialization of window
	settings.antialiasingLevel = 8;
	RenderWindow window(sf::VideoMode(640, 480), "lab 7.2", Style::Default, settings);

	StartProgram(window, blocks, stateIndex);
}