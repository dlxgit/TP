#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "windows.h"
#include "main.h"

using namespace std;
using namespace sf;

void GetFilesDirectory(string dir, Settings & settings, int n)
{
	int index;
	string strDir = { NULL };  //directory of file(folder)
	dir.pop_back();
	strDir = dir;

	settings.names[n] = strDir + settings.names[n];
}

void FindFiles(string & dir, Settings & settings)
{
	HANDLE handle;
	WIN32_FIND_DATA findData;

	handle = FindFirstFile(dir.c_str(), &findData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		settings.state = INVALID_DIR;
	}
	else
	{
		int k = 0;
		do
		{
			if (k == 0)
			{
				settings.state = EMPTY_DIR;
			}
			else settings.state = SHOW_IMAGE;
			{
				string str;
				str = findData.cFileName;

				string String0(str);
				string subStr = String0.substr(String0.find_last_of(".") + 1);  //file extension
				if ((subStr == "png") || (subStr == "jpeg") || (subStr == "jpg") || (subStr == "bmp"))
				{
					settings.names.push_back(findData.cFileName);
					std::cout << settings.names[k] << endl;
					settings.nFiles++;
					GetFilesDirectory(dir, settings, k);
					k++;
				}
			}
		} while (FindNextFile(handle, &findData) != 0);
	}
	FindClose(handle);
}

bool OpenImage(Settings & settings)
{
	Texture texture;

	if (texture.loadFromFile(settings.names[settings.index]))
	{
		settings.texture = texture;
		settings.sprite.setTexture(settings.texture);
		return true;
	}
	else
	{
		//error loading text
		return false;
	}
}

void ResetDefaultVariables(Settings & settings)
{
	settings.zoom = 1;
	settings.mouseDrag.x = 0;
	settings.mouseDrag.y = 0;
}

bool IsEvent(Vector2f & mousePosition, Settings & settings, RenderWindow & window, Buttons & buttons)
{
	bool isEvent = false;
	Event event;
	//if mouseLeft is pressed and it is on position of buttons.left image
	if (Keyboard::isKeyPressed(Keyboard::Left) || (buttons.left.getGlobalBounds().contains(mousePosition.x * WIDTH_BASIC / settings.windowSize.x, mousePosition.y * HEIGHT_BASIC / settings.windowSize.y) && Mouse::isButtonPressed(Mouse::Left)))
	{
		if (settings.isButtonPressed == false)
		{
			settings.isButtonPressed = true;
			settings.index -= 1;
			if (settings.index <= -1)
			{
				settings.index = settings.nFiles - 1;
			}
			ResetDefaultVariables(settings);
			buttons.left.setTextureRect(IntRect(121, 0, 121, 120));
			isEvent = true;

			if (OpenImage(settings) == false)
			{
				settings.state = UNABLE_TO_LOAD;
			}
		}
	}
	//if mouseRight is pressed and it is on position of buttons.right image
	else if (Keyboard::isKeyPressed(Keyboard::Right) || (buttons.right.getGlobalBounds().contains(mousePosition.x * WIDTH_BASIC / settings.windowSize.x, mousePosition.y * HEIGHT_BASIC / settings.windowSize.y) && Mouse::isButtonPressed(Mouse::Left)))
	{
		if (settings.isButtonPressed == false)
		{
			settings.isButtonPressed = true;
			settings.index += 1;
			if (settings.index >= settings.nFiles - 1)
			{
				settings.index = 0;
			}
			ResetDefaultVariables(settings);
			buttons.right.setTextureRect(IntRect(363, 0, 121, 120));
			isEvent = true;
			if (OpenImage(settings) == false)
			{
				settings.state = UNABLE_TO_LOAD;
			}
		}
	}

	if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Add))
	{
		settings.zoom += 1;
		if (settings.zoom > 4) settings.zoom = 4;
		isEvent = true;
	}
	else if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Subtract))
	{
		settings.zoom -= 1;
		if (settings.zoom < 1) settings.zoom = 1;
		isEvent = true;
	}
	return isEvent;
}

bool ProcessEvents(RenderWindow & window, Settings & settings, Buttons & buttons)
{
	Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

	settings.windowSize = static_cast<sf::Vector2f>(window.getSize());

	bool isEvent = false;

	Event event;
	while (window.pollEvent(event))
	{
		if (window.hasFocus())
		{
			if (IsEvent(mousePosition, settings, window, buttons))
			{
				isEvent = true;
			}
			else 
			{
				buttons.left.setTextureRect(IntRect(0, 0, 121, 120));
				buttons.right.setTextureRect(IntRect(242, 0, 121, 120));

				if (Mouse::isButtonPressed(Mouse::Left) == false)
				{
					settings.isButtonPressed = false;
					settings.mouseLastPos = static_cast<sf::Vector2f>(Mouse::getPosition(window)) + settings.mouseDrag;
				}
				else settings.isButtonPressed = true;

				buttons.left.setTextureRect(IntRect(0, 0, 121, 120));
				buttons.right.setTextureRect(IntRect(242, 0, 121, 120));

				if (settings.isButtonPressed == true)
				{
					settings.mouseDrag.x = (settings.mouseLastPos.x - mousePosition.x);
					settings.mouseDrag.y = (settings.mouseLastPos.y - mousePosition.y);
					isEvent = true;
				}
			}
		}
	}
	if (settings.isChanged)
	{
		isEvent = true;
		settings.isChanged = false;
	}
	if (event.type == Event::Resized)
	{
		isEvent = true;
	}

	if (event.type == Event::Closed)
	{
		window.close();
	}
	return isEvent;
}

void ComputeImageSettings(RenderWindow & window, Settings & settings)
{
	Sprite image;
	image.setTexture(settings.texture);
	window.setTitle(settings.names[settings.index]);
	FloatRect imageRect = image.getGlobalBounds();
	settings.imageSize = { imageRect.width,imageRect.height };
	settings.windowSize = static_cast<sf::Vector2f>(window.getSize());

	float ScaleX;
	float ScaleY;
	ScaleX = WIDTH_BASIC / settings.windowSize.x;
	ScaleY = HEIGHT_BASIC / settings.windowSize.y;
	float Scale = 1;

	if (settings.windowSize.x < settings.imageSize.x && settings.windowSize.y < settings.imageSize.y)
	{
		if (settings.imageSize.x / settings.imageSize.y >= settings.windowSize.x / settings.windowSize.y)
		{
			Scale = settings.windowSize.x / settings.imageSize.x;
		}
		else if (settings.imageSize.x / settings.imageSize.y < settings.windowSize.x / settings.windowSize.y)
		{
			Scale = settings.windowSize.y / settings.imageSize.y;
		}
	}
	//if image is larger than window
	if ((settings.imageSize.x * ScaleX * Scale * settings.zoom > WIDTH_BASIC) || (settings.imageSize.y * ScaleY * Scale * settings.zoom > HEIGHT_BASIC))
	{
		image.setOrigin((settings.mouseDrag.x) * abs(settings.windowSize.x - settings.imageSize.x) / (settings.windowSize.x * settings.zoom), settings.mouseDrag.y * abs(settings.windowSize.y - settings.imageSize.y) / (settings.windowSize.y * settings.zoom));
	}
	else
	{
		image.setOrigin(0, 0);
	}
	image.setPosition(WIDTH_BASIC / 2 - (settings.imageSize.x / 2) * ScaleX * Scale * settings.zoom, HEIGHT_BASIC / 2 - (settings.imageSize.y / 2) * ScaleY * Scale * settings.zoom);
	image.setScale(ScaleX * Scale * settings.zoom, ScaleY * Scale * settings.zoom);
	settings.scale = { ScaleX, ScaleY };
	settings.sprite = image;
}

void ComputeButtonSettings(RenderWindow & window, Settings & settings, Buttons & buttons)
{
	buttons.left.setScale(float(0.5) * settings.scale.x, float(0.5) * settings.scale.y);
	buttons.right.setScale(float(0.5) * settings.scale.x, float(0.5) * settings.scale.y);

	//30 and 50 are numbers of distance between sprites and right bottom border of window
	buttons.left.setPosition(0, (settings.windowSize.y / 2 - 30) * HEIGHT_BASIC / settings.windowSize.y);
	buttons.right.setPosition((settings.windowSize.x - 60) * WIDTH_BASIC / settings.windowSize.x, (settings.windowSize.y / 2 - 30) * HEIGHT_BASIC / settings.windowSize.y);
}

void DrawImage(RenderWindow & window, Settings & settings)
{
	window.draw(settings.sprite);
}

void DrawButtons(RenderWindow & window, Buttons & buttons)
{
	window.draw(buttons.left);
	window.draw(buttons.right);
}

void CheckWindowClose(RenderWindow & window)
{
	Event event;
	while (window.pollEvent(event))
	{
		if (event.type == Event::Closed)
			window.close();
	}
}

void EmptyDirEvent(RenderWindow & window, Text & text)
{
	text.setString("There are no images in directory");
	text.setPosition(90, 180);
	window.draw(text);
}

void InvalidDirEvent(RenderWindow & window, Text & text)
{
	text.setString("Directory is not found");
	text.setPosition(150, 180);
	window.draw(text);
}

void LoadingErrorEvent(RenderWindow & window, Text & text)
{
	text.setString("Failed to load file...");
	text.setPosition(215, 180);
	window.draw(text);
}

void LoadingText(RenderWindow & window, Text & text)
{
	text.setString("Loading File...");
	text.setPosition(215, 180);
	window.draw(text);
}

void main()
{
	Settings settings;
	Buttons buttons;

	settings.nFiles = 0;
	settings.isChanged = false;
	settings.zoom = 1;
	settings.isButtonPressed = false;
	settings.mouseLastPos = { 0,0 };
	settings.mouseDrag = { 0,0 };
	settings.scale = { 1, 1 };

	buttons.textureButtons.loadFromFile("images/buttons.png");
	buttons.left.setTexture(buttons.textureButtons);
	buttons.right.setTexture(buttons.textureButtons);
	buttons.left.setTextureRect(IntRect(0, 0, 121, 120));
	buttons.right.setTextureRect(IntRect(242, 0, 121, 120));
	buttons.left.setScale(0.5, 0.5);
	buttons.right.setScale(0.5, 0.5);
	buttons.left.setPosition(30, 210);
	buttons.right.setPosition(550, 210);
	buttons.textureZoom.loadFromFile("images/zoom.png");

	//text
	Font font;
	font.loadFromFile("Font/Arialbd.ttf");
	Text text("", font, 30);
	text.setColor(Color::Black);

	string dir;  //directory(path)
	cout << "input directory (for example: d:/images/*):  ";

	if (cin >> dir)
	{
		FindFiles(dir, settings);	
		settings.index = 0;
		RenderWindow window(sf::VideoMode(WIDTH_BASIC, HEIGHT_BASIC), "ImageViewer");
		window.setTitle("ImageViewer");

		if (settings.state != INVALID_DIR && settings.state != EMPTY_DIR)
		{
			//window.setTitle(images->names[settings.index]);
			if (OpenImage(settings))
			{
				settings.state = SHOW_IMAGE;
			}
			else
			{
				settings.state = UNABLE_TO_LOAD;
			}
		}
		ComputeImageSettings(window, settings);
		ComputeButtonSettings(window, settings, buttons);
	
		//main cycle
		while (window.isOpen())
		{
			window.clear(Color::White);

			cout << settings.index << endl;
			if (settings.state == SHOW_IMAGE)
			{
				//if any event detected(pressed button or resized)
				if (ProcessEvents(window, settings, buttons))
				{
					ComputeImageSettings(window, settings);
					ComputeButtonSettings(window, settings, buttons);
				}
				DrawImage(window, settings);
				DrawButtons(window, buttons);
			}
			else if (settings.state == UNABLE_TO_LOAD)
			{
				LoadingErrorEvent(window, text);
				if (ProcessEvents(window, settings, buttons))
				{
					settings.isChanged = true;
					ComputeImageSettings(window, settings);
					ComputeButtonSettings(window, settings, buttons);
					if (OpenImage(settings))
					{
						settings.state = SHOW_IMAGE;
					}
				}
				DrawButtons(window, buttons);
			}
			else if (settings.state == EMPTY_DIR)
			{
				EmptyDirEvent(window, text);
				CheckWindowClose(window);
			}
			else if (settings.state == INVALID_DIR)
			{
				InvalidDirEvent(window, text);
				CheckWindowClose(window);
			}
			window.display();
		}		
	}
}