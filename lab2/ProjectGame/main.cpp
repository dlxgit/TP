#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include "map.h"
#include "game.h"
#include "snake.h"
#include "apple.h"

using namespace sf;

void main()
{
	Game * game;
	game = new Game();
	InitializeGame(game);

	Snake * snake;
	snake = new Snake();
	InitializeSnake(snake);

	Apple * apple;
	apple = new Apple();
	InitializeApple(apple, snake);

	Clock clock;

	RenderWindow window(sf::VideoMode(WIDTH, HEIGHT),"Snake");

	while (window.isOpen())
	{
		window.clear();

		//checkWindowClose
		Event event;
		while (window.pollEvent(event))
			if (event.type == Event::Closed)
				window.close();

		switch (game->state)
		{
		case BEGIN:
			BeginEvent(window,game, snake);
			break;
		case END:
			EndGameEvent(window,game, snake);
			break;
		case CONTINUE:
			game->time = 0; 
			while (game->time < TIME_STEP) 
			{
				ProcessEvents(window, snake);
				game->time = clock.getElapsedTime().asMilliseconds(); //get time in milliseconds
			}

			if (game->time >= TIME_STEP)
			{
				clock.restart();   //reloading time

				//update
				ProcessEvents(window, snake);       // direction
				Tick(snake);						// parts
				Update(snake);                      // position

				//check
				CheckEventApple(snake, apple);      
				CheckGameOver(game, snake);       

				//draw
				DrawField(window,game); 
				DrawSnake(window, snake);        
				DrawApple(window, apple);   
			}
			break;
		}
		window.display();
	}
}