#include "pendulum.h"

void InitializePendulum(Pendulum & pendulum)
{
	pendulum.firstWheel.texture.loadFromFile("resources/detail.png");
	pendulum.secondWheel.texture = pendulum.firstWheel.texture;
	pendulum.firstWheel.sprite.setTexture(pendulum.firstWheel.texture);
	pendulum.secondWheel.sprite.setTexture(pendulum.firstWheel.texture);

	float wheelRadius = pendulum.firstWheel.sprite.getGlobalBounds().width / 2;
	pendulum.firstWheel.sprite.setPosition(FIRST_WHEEL_POS);
	pendulum.firstWheel.sprite.setOrigin(wheelRadius, wheelRadius);
	pendulum.firstWheel.rotation = 0;
	pendulum.secondWheel.sprite.setPosition(SECOND_WHEEL_POS);
	pendulum.secondWheel.sprite.setOrigin(wheelRadius, wheelRadius);
	pendulum.secondWheel.rotation = 0;
	pendulum.speed = 0;
	pendulum.rotation = START_ROTATION;

	pendulum.turn.setPointCount(4);
	pendulum.turn.setPoint(0, sf::Vector2f(0, 200));
	pendulum.turn.setPoint(1, sf::Vector2f(100, 100));
	pendulum.turn.setPoint(2, sf::Vector2f(200, 200));
	pendulum.turn.setPoint(3, sf::Vector2f(100, 100));
	pendulum.turn.setFillColor(Color::Black);
	pendulum.turn.setOrigin(100, 100);
	pendulum.turn.setPosition(PENDULUM_POS);
	pendulum.weight.setPointCount(5);
	pendulum.weight.setPoint(0, sf::Vector2f(100, 100));
	pendulum.weight.setPoint(1, sf::Vector2f(120, 400));
	pendulum.weight.setPoint(2, sf::Vector2f(160, 440));
	pendulum.weight.setPoint(3, sf::Vector2f(40, 440));
	pendulum.weight.setPoint(4, sf::Vector2f(80, 400));
	pendulum.weight.setFillColor(Color::Black);
	pendulum.weight.setOrigin(100, 100);
	pendulum.weight.setPosition(PENDULUM_POS);
};

void UpdatePendulum(Pendulum & pendulum)
{
	pendulum.weight.setRotation(pendulum.rotation);
	pendulum.turn.setRotation(pendulum.rotation);
	pendulum.firstWheel.sprite.setRotation(pendulum.firstWheel.rotation);
	pendulum.secondWheel.sprite.setRotation(pendulum.secondWheel.rotation);
};

void ComputePhysics(Pendulum & pendulum)
{
	if (pendulum.rotation > 0)
	{
		pendulum.speed -= ACCELERATION;
	}
	else pendulum.speed += ACCELERATION;

	pendulum.rotation += pendulum.speed;
	pendulum.firstWheel.rotation += pendulum.speed / 2.f;
	pendulum.secondWheel.rotation = -pendulum.firstWheel.rotation;
};