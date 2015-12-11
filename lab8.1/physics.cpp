#include "physics.h"


void InitializePhysics(Physics & physics)
{
	physics.slowingPos = 0;
	physics.speed = 0;
	physics.carPos = START_POS;
}


void ComputePhysics(Physics & physics)
{
	if (physics.speed == 0)
	{
		physics.slowingPos = physics.carPos.x + (WINDOW_SIZE.x - physics.carPos.x - CAR_WIDTH) / 2.f;
	}
	if (physics.carPos.x < physics.slowingPos)
	{
		physics.speed += ACCELERATION;
	}
	else if ((physics.carPos.x + CAR_WIDTH) < WINDOW_SIZE.x)
	{
		physics.speed -= ACCELERATION;
	}
	physics.carPos.x += physics.speed;
	physics.rotation = (physics.speed / M_PI) * 360.0f;
}
