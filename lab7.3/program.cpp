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
};


void StartProgram(RenderWindow & window, Pendulum & pendulum)
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

			ComputePhysics(pendulum);
			UpdatePendulum(pendulum);

			window.clear(Color::White);
			Draw(window, pendulum);
			window.display();
		}
	}
};