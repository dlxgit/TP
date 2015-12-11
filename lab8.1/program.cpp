#include "program.h"

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

void Draw(RenderWindow & window, Car & car, const RectangleShape & ground)
{
	window.draw(ground);
	window.draw(car.sprite);
	window.draw(car.backWheel.sprite);
	window.draw(car.frontWheel.sprite);
}

void StartProgram(RenderWindow & window, Car & car, Physics & physics, const RectangleShape & ground)
{
	Clock frameClock;
	int timeSinceLastFrame;

	while (window.isOpen())
	{
		timeSinceLastFrame = frameClock.getElapsedTime().asMilliseconds();
		ProcessEvents(window);
		if (timeSinceLastFrame >= TIME_PER_FRAME)
		{
			frameClock.restart();

			ComputePhysics(physics);
			UpdateCar(car, physics);

			window.clear(Color::White);
			Draw(window, car, ground);
			window.display();
		}
	}
}