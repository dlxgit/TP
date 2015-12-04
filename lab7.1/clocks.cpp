#include "Clocks.h"

void InitializeMarkers(RectangleShape * markers)
{
	Vector2f bigMarkerSize = { 12,4 };   //size of shape
	Vector2f smallMarkerSize = { 4,2 };  //size of shape
	float radius = 160;                  //radius of markers(for computing position)

	for (int i = 0; i < 12; i++)
	{
		float angle = (360 - (float(i) * float(360) / float(12))) - 90;
		Vector2f pos = { CLOCK_CENTER.x + cos(float(angle) * float(M_PI) / float(180)) * radius + 3, CLOCK_CENTER.y + sin(float(angle) * float(M_PI) / float(180)) * radius + 3 };

		if (i % 3 == 0)	markers[i].setSize(bigMarkerSize);
		else markers[i].setSize(smallMarkerSize);

		markers[i].setPosition(pos);
		markers[i].setRotation(angle - 180);
		markers[i].setFillColor(Color::Black);
	}
}

void InitializeClocks(Clocks & clocks)
{
	clocks.circle.setRadius(float(CIRCLE_RADIUS));
	clocks.circle.setPosition(CIRCLE_POS);
	clocks.circle.setFillColor(Color::White);
	clocks.circle.setOutlineThickness(10);
	clocks.circle.setOutlineColor(Color::Blue);

	clocks.circle.setPointCount(60);  //better circle quality

	clocks.centerCircle.setRadius(10);
	clocks.centerCircle.setPosition(Vector2f(193, 193));
	clocks.centerCircle.setFillColor(Color::Red);

	InitializeMarkers(clocks.markers);
}

void DrawMarkers(RenderWindow & window, RectangleShape(&markers)[12])
{
	for (int i = 0; i < 12; i++)
	{
		window.draw(markers[i]);
	}
}

void Draw(RenderWindow & window, Clocks & clocks, Hands & hands)
{
	window.draw(clocks.circle);
	DrawMarkers(window, clocks.markers);
	DrawHands(window, hands);
	window.draw(clocks.centerCircle);
}