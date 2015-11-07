#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "windows.h"
#include <stdio.h>

using namespace std;
using namespace sf;

const int WIDTH_BASIC = 640;
const int HEIGHT_BASIC = 480;

enum State
{
	SHOW_IMAGE,
	INVALID_DIR,
	EMPTY_DIR,
	UNABLE_TO_LOAD
};

struct
{
	char name[150]; //fileName
	char dir[150];  //directory as array of char
	Texture texture;
	Sprite sprite;
	bool isLoaded;
}FileStruct[200];


void GetFileDirectory(int &fileIndex, char dir[])
{
	int index;
	char strDir[150] = { NULL };  //directory of file(folder) as array of char
	for (int i = 0; dir[i]; i++)
	{
		strDir[i] = dir[i];
		index = i;
	}
	for (int i = 0; FileStruct[fileIndex].name[i]; i++)
	{
		strDir[index + i] = FileStruct[fileIndex].name[i];
	}
	strcpy(FileStruct[fileIndex].dir, strDir);
}

void FindFiles(State & state, char(&dir)[150])
{
	HANDLE handle;
	WIN32_FIND_DATA findData;

	handle = FindFirstFile(dir, &findData);

	if (handle == INVALID_HANDLE_VALUE)
	{
		state = INVALID_DIR;
	}
	else
	{
		int k = 0;
		do
		{
			if (k == 0)
			{
				state = EMPTY_DIR;
			}
			else state = SHOW_IMAGE;
			{
				char str[300] = { NULL };
				strcpy(str, findData.cFileName);
				string String0(str);
				string subStr = String0.substr(String0.find_last_of(".") + 1);  //file extension
				if ((subStr == "png") || (subStr == "jpeg") || (subStr == "jpg") || (subStr == "bmp"))
				{
					strcpy(FileStruct[k].name, findData.cFileName);
					cout << FileStruct[k].name << endl;
					k++;
				}
			}
		} while (FindNextFile(handle, &findData) != 0);
	}
	FindClose(handle);
}

bool OpenImage(int &fileIndex, char dir[])
{
	bool isImageLoaded = false;

	if (FileStruct[fileIndex].isLoaded == false)
	{
		Texture texture;

		GetFileDirectory(fileIndex, dir);
		if (texture.loadFromFile(FileStruct[fileIndex].dir))
		{
			isImageLoaded = true;

			FileStruct[fileIndex].texture = texture;
			FileStruct[fileIndex].isLoaded = true;
		}
	}
	else isImageLoaded = true;
	return isImageLoaded;
}

int GetLastFileIndex()
{
	int lastFileIndex;
	lastFileIndex = 0;

	while (FileStruct[lastFileIndex].name[0] != NULL)
		lastFileIndex += 1;
	lastFileIndex += 1;
	return lastFileIndex;
}

void ResetDefaultVariables(int & zoom, Vector2i & mouseDragDifference)
{
	zoom = 1;
	mouseDragDifference.x = 0;
	mouseDragDifference.y = 0;
}

bool ProcessEvents(RenderWindow & window, int & fileIndex, Sprite & buttonLeft, Sprite & buttonRight, int & zoom, Vector2i & mouseLastInactivePos, Vector2i & mouseDragDifference, bool & isMousePressed)
{
	Vector2i mousePosition = Mouse::getPosition(window);

	float windowSizeX = window.getSize().x;
	float windowSizeY = window.getSize().y;

	bool isEvent = false;

	Event event;
	while (window.pollEvent(event))
	{
		if (window.hasFocus())
		{
			//if mouseLeft is pressed and it is on position of buttonLeft image
			if (Keyboard::isKeyPressed(Keyboard::Left) || (buttonLeft.getGlobalBounds().contains(mousePosition.x * WIDTH_BASIC / windowSizeX, mousePosition.y * HEIGHT_BASIC / windowSizeY) && Mouse::isButtonPressed(Mouse::Left)))
			{
				if (isMousePressed == false)
				{
					isMousePressed = true;

					fileIndex -= 1;
					if (fileIndex == -1)fileIndex = GetLastFileIndex();
					window.setTitle(FileStruct[fileIndex].name);
					ResetDefaultVariables(zoom, mouseDragDifference);
					buttonLeft.setTextureRect(IntRect(121, 0, 121, 120));

					isEvent = true;
				}
			}
			//if mouseRight is pressed and it is on position of buttonRight image
			else if (Keyboard::isKeyPressed(Keyboard::Right) || (buttonRight.getGlobalBounds().contains(mousePosition.x * WIDTH_BASIC / windowSizeX, mousePosition.y * HEIGHT_BASIC / windowSizeY) && Mouse::isButtonPressed(Mouse::Left)))
			{
				if (isMousePressed == false)
				{
					isMousePressed = true;
					fileIndex += 1;
					if (fileIndex == GetLastFileIndex() + 1)fileIndex = 0;
					window.setTitle(FileStruct[fileIndex].name);
					ResetDefaultVariables(zoom, mouseDragDifference);

					buttonRight.setTextureRect(IntRect(363, 0, 121, 120));

					isEvent = true;
				}
			}

			else
			{
				buttonLeft.setTextureRect(IntRect(0, 0, 121, 120));
				buttonRight.setTextureRect(IntRect(242, 0, 121, 120));

				if (Mouse::isButtonPressed(Mouse::Left) == false)
				{
					isMousePressed = false;
					mouseLastInactivePos = Mouse::getPosition(window) + mouseDragDifference;
				}
				else isMousePressed = true;

				buttonLeft.setTextureRect(IntRect(0, 0, 121, 120));
				buttonRight.setTextureRect(IntRect(242, 0, 121, 120));

				isEvent = true;
				if (isMousePressed == true)
				{
					mouseDragDifference.x = (mouseLastInactivePos.x - mousePosition.x);
					mouseDragDifference.y = (mouseLastInactivePos.y - mousePosition.y);
				}
			}

			if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Add))
			{
				zoom += 1;
				if (zoom > 4) zoom = 4;
				isEvent = true;
			}
			else if ((Keyboard::isKeyPressed(Keyboard::LControl) || Keyboard::isKeyPressed(Keyboard::RControl)) && Keyboard::isKeyPressed(Keyboard::Subtract))
			{
				zoom -= 1;
				if (zoom < 1) zoom = 1;
				isEvent = true;
			}

			if (event.type == Event::Resized)
			{
				isEvent = true;
			}

			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
	}
	return isEvent;
}

void computeImageSettings(RenderWindow & window, int & fileIndex, int & zoom, Sprite & buttonLeft, Sprite & buttonRight, Vector2i & mouseDragDifference)
{
	Sprite image;
	image.setTexture(FileStruct[fileIndex].texture);

	FloatRect imageRect = image.getGlobalBounds();
	float imageSizeX;
	float imageSizeY;
	imageSizeX = imageRect.width;
	imageSizeY = imageRect.height;

	float windowSizeX;  //window size
	float windowSizeY;  //window size
	windowSizeX = window.getSize().x;
	windowSizeY = window.getSize().y;

	float ScaleX;
	float ScaleY;
	ScaleX = WIDTH_BASIC / windowSizeX;
	ScaleY = HEIGHT_BASIC / windowSizeY;

	float Scale = 1;

	//scaling
	if (imageSizeX <= windowSizeX && imageSizeY <= windowSizeY) {}

	else if (windowSizeY < imageSizeY && windowSizeX >= imageSizeX)
	{
		Scale = windowSizeY / imageSizeY;
	}
	else if (windowSizeX < imageSizeX && windowSizeY >= imageSizeY)
	{
		Scale = windowSizeX / imageSizeX;
	}
	else if (windowSizeX < imageSizeX && windowSizeY < imageSizeY)
	{
		if (imageSizeX / imageSizeY >= windowSizeX / windowSizeY)
		{
			Scale = windowSizeX / imageSizeX;
		}
		else if (imageSizeX / imageSizeY < windowSizeX / windowSizeY)
		{
			Scale = windowSizeY / imageSizeY;
		}
	}

	//if image is larger than window
	if ((imageSizeX * ScaleX * Scale * zoom > WIDTH_BASIC) || (imageSizeY * ScaleY * Scale * zoom > HEIGHT_BASIC))
	{
		image.setOrigin(int((mouseDragDifference.x) * abs(windowSizeX - imageSizeX) / (windowSizeX * zoom)), int(mouseDragDifference.y * abs(windowSizeY - imageSizeY) / (windowSizeY * zoom)));
	}
	else
	{
		image.setOrigin(0, 0);
	}

	image.setPosition(WIDTH_BASIC / 2 - (imageSizeX / 2) * ScaleX * Scale * zoom, HEIGHT_BASIC / 2 - (imageSizeY / 2) * ScaleY * Scale * zoom);
	image.setScale(ScaleX * Scale * zoom, ScaleY * Scale * zoom);

	window.setTitle(FileStruct[fileIndex].name);
	FileStruct[fileIndex].sprite = image;
}

void computeButtonSettings(RenderWindow & window, int & zoom, Sprite & buttonLeft, Sprite & buttonRight, Sprite & buttonPlus, Sprite & buttonMinus)
{
	float windowSizeX;
	float windowSizeY;
	windowSizeX = window.getSize().x;
	windowSizeY = window.getSize().y;

	float ScaleX;
	float ScaleY;
	ScaleX = WIDTH_BASIC / windowSizeX;
	ScaleY = HEIGHT_BASIC / windowSizeY;

	if (zoom > 1)
	{
		buttonMinus.setTextureRect(IntRect(44, 83, 40, 40));
	}
	else
	{
		buttonMinus.setTextureRect(IntRect(172, 83, 40, 40));
	}
	if (zoom < 5)
	{
		buttonPlus.setTextureRect(IntRect(44, 26, 40, 40));
	}
	else
	{
		buttonPlus.setTextureRect(IntRect(172, 26, 40, 40));
	}

	buttonPlus.setScale(ScaleX, ScaleY);
	buttonMinus.setScale(ScaleX, ScaleY);
	buttonLeft.setScale(0.5 * ScaleX, 0.5 * ScaleY);
	buttonRight.setScale(0.5 * ScaleX, 0.5 * ScaleY);

	//30 and 50 are numbers of distance between sprites and right bottom border of window
	buttonPlus.setPosition((windowSizeX - 50) * WIDTH_BASIC / windowSizeX, (windowSizeY - 50) * HEIGHT_BASIC / windowSizeY);
	buttonMinus.setPosition((windowSizeX - 100) * WIDTH_BASIC / windowSizeX, (windowSizeY - 50) * HEIGHT_BASIC / windowSizeY);
	buttonLeft.setPosition(0, (windowSizeY / 2 - 30) * HEIGHT_BASIC / windowSizeY);
	buttonRight.setPosition((windowSizeX - 60) * WIDTH_BASIC / windowSizeX, (windowSizeY / 2 - 30) * HEIGHT_BASIC / windowSizeY);
}

void DrawImage(RenderWindow & window, int  fileIndex)
{
	window.draw(FileStruct[fileIndex].sprite);
}

void DrawButtons(RenderWindow & window, Sprite & buttonLeft, Sprite & buttonRight, Sprite & buttonPlus, Sprite & buttonMinus)
{
	window.draw(buttonLeft);
	window.draw(buttonRight);
	window.draw(buttonPlus);
	window.draw(buttonMinus);
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

//functions of printing text
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
	//images
	Texture buttonsTexture;
	buttonsTexture.loadFromFile("images/buttons.png");
	Sprite buttonLeft;
	Sprite buttonRight;
	buttonLeft.setTexture(buttonsTexture);
	buttonRight.setTexture(buttonsTexture);
	buttonLeft.setTextureRect(IntRect(0, 0, 121, 120));
	buttonRight.setTextureRect(IntRect(242, 0, 121, 120));
	buttonLeft.setScale(0.5, 0.5);
	buttonRight.setScale(0.5, 0.5);
	buttonLeft.setPosition(30, 210);
	buttonRight.setPosition(550, 210);
	Texture zoomTexture;
	zoomTexture.loadFromFile("images/zoom.png");
	Sprite buttonPlus;
	Sprite buttonMinus;
	buttonPlus.setTexture(zoomTexture);
	buttonMinus.setTexture(zoomTexture);
	buttonPlus.setTextureRect(IntRect(43, 26, 40, 40));
	buttonMinus.setTextureRect(IntRect(43, 103, 40, 40));

	//text
	Font font;
	font.loadFromFile("Font/Arialbd.ttf");
	Text text("", font, 30);
	text.setColor(Color::Black);

	State state;
	int zoom = 1;
	bool isMousePressed = false;
	Vector2i mouseLastInactivePos;
	Vector2i mouseDragDifference;
	mouseDragDifference.x = 0;
	mouseDragDifference.y = 0;

	char dir[150];  //directory(path)
	cout << "input directory (for example: d:/images/*) :";

	if (cin >> dir)
	{
		FindFiles(state, dir);

		int fileIndex = 0;
		RenderWindow window(sf::VideoMode(WIDTH_BASIC, HEIGHT_BASIC), "ImageViewer");
		window.setTitle("ImageViewer");

		if (state != INVALID_DIR && state != EMPTY_DIR)
		{
			window.setTitle(FileStruct[fileIndex].name);
			if (OpenImage(fileIndex, dir)) state = SHOW_IMAGE;
			else state = UNABLE_TO_LOAD;
		}

		computeImageSettings(window, fileIndex, zoom, buttonLeft, buttonRight, mouseDragDifference);
		computeButtonSettings(window, zoom, buttonLeft, buttonRight, buttonPlus, buttonMinus);
		//main cycle
		while (window.isOpen())
		{
			window.clear(Color::White);

			if (state == SHOW_IMAGE)
			{
				//if any event detected(pressed button or resized)
				if (ProcessEvents(window, fileIndex, buttonLeft, buttonRight, zoom, mouseLastInactivePos, mouseDragDifference, isMousePressed))
				{
					computeImageSettings(window, fileIndex, zoom, buttonLeft, buttonRight, mouseDragDifference);
					computeButtonSettings(window, zoom, buttonLeft, buttonRight, buttonPlus, buttonMinus);
					if (OpenImage(fileIndex, dir) == false)
					{
						state = UNABLE_TO_LOAD;
					}
				}

				DrawImage(window, fileIndex);
				DrawButtons(window, buttonLeft, buttonRight, buttonPlus, buttonMinus);
			}
			else if (state == UNABLE_TO_LOAD)
			{
				LoadingErrorEvent(window, text);
				if (ProcessEvents(window, fileIndex, buttonLeft, buttonRight, zoom, mouseLastInactivePos, mouseDragDifference, isMousePressed))
				{
					computeImageSettings(window, fileIndex, zoom, buttonLeft, buttonRight, mouseDragDifference);
					computeButtonSettings(window, zoom, buttonLeft, buttonRight, buttonPlus, buttonMinus);
					if (OpenImage(fileIndex, dir))
						state = SHOW_IMAGE;
				}
				DrawButtons(window, buttonLeft, buttonRight, buttonPlus, buttonMinus);
			}
			else if (state == EMPTY_DIR)
			{
				EmptyDirEvent(window, text);
				CheckWindowClose(window);
			}
			else if (state == INVALID_DIR)
			{
				InvalidDirEvent(window, text);
				CheckWindowClose(window);
			}
			window.display();
		}
	}
}