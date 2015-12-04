#include "hands.h"

void InitializeHands(Hands & hands)
{
	Vector2f center = { 200,200 };

	hands.hour.line.setFillColor(Color::Black);
	hands.minute.line.setFillColor(Color::Green);
	hands.second.line.setFillColor(Color::Red);

	hands.hour.line.setPosition(Vector2f(center.x + 2, center.y + 2));
	hands.hour.line.setSize(Vector2f(73, 3));
	hands.hour.maxTime = 12;
	hands.hour.angle = 360 / hands.hour.maxTime;

	hands.minute.line.setPosition(Vector2f(center.x + 2, center.y + 2));
	hands.minute.line.setSize(Vector2f(85, 3));
	hands.minute.maxTime = 60;
	hands.minute.angle = 360 / hands.minute.maxTime;

	hands.second.line.setPosition(Vector2f(center.x + 2, center.y + 2));
	hands.second.line.setSize(Vector2f(105, 3));
	hands.second.maxTime = 60;
	hands.second.angle = 360 / hands.second.maxTime;
};


void ComputeHandsPosition(Hands & hands)
{
	float angle;
	angle = hands.second.time * 360 / hands.second.maxTime - 90;
	hands.second.line.setRotation(angle);
	angle = hands.minute.time * 360 / hands.minute.maxTime + (hands.second.time / hands.second.maxTime) * hands.minute.angle - 90;
	hands.minute.line.setRotation(angle);
	angle = hands.hour.time * 360 / hands.hour.maxTime + (hands.minute.time / hands.minute.maxTime) * hands.hour.angle - 90;
	hands.hour.line.setRotation(angle);
}

void UpdateClockTime(Hands & hands)
{
	SYSTEMTIME time;
	GetSystemTime(&time);

	hands.second.time = time.wSecond;
	hands.minute.time = time.wMinute;
	hands.hour.time = time.wHour + float(3);
}

void DrawHands(RenderWindow & window, Hands & hands)
{
	window.draw(hands.second.line);
	window.draw(hands.minute.line);
	window.draw(hands.hour.line);
}