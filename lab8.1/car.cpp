#include "car.h"

void InitializeCar(Car & car)
{
	car.texture.loadFromFile("resources/car.png");
	car.sprite.setTexture(car.texture);
	car.sprite.setPosition(START_POS);
	car.width = car.sprite.getGlobalBounds().width;
	car.backWheel.texture.loadFromFile("resources/wheel.png");
	car.backWheel.sprite.setTexture(car.backWheel.texture);
	car.frontWheel.sprite.setTexture(car.backWheel.texture);

	float wheelRadius = car.backWheel.sprite.getGlobalBounds().width / 2;

	car.backWheel.sprite.setPosition(START_POS.x + BACK_WHEEL_POS.x, START_POS.y + BACK_WHEEL_POS.y);
	car.frontWheel.sprite.setPosition(START_POS.x + BACK_WHEEL_POS.x + WHEEL_DISTANCE, START_POS.y + BACK_WHEEL_POS.y);
	car.backWheel.sprite.setOrigin(wheelRadius, wheelRadius);
	car.frontWheel.sprite.setOrigin(wheelRadius, wheelRadius);
}

void UpdateCar(Car & car, Physics & physics)
{
	car.sprite.setPosition(physics.carPos);
	car.backWheel.sprite.setPosition(physics.carPos.x + BACK_WHEEL_POS.x, physics.carPos.y + BACK_WHEEL_POS.y);
	car.backWheel.sprite.rotate(physics.rotation / car.backWheel.sprite.getGlobalBounds().width);
	car.frontWheel.sprite.setPosition(physics.carPos.x + BACK_WHEEL_POS.x + WHEEL_DISTANCE, physics.carPos.y + BACK_WHEEL_POS.y);
	car.frontWheel.sprite.rotate(physics.rotation / car.backWheel.sprite.getGlobalBounds().width);
}