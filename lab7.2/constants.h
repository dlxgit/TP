#pragma once
#include <SFML/Graphics.hpp>

const static sf::Vector2f WINDOW_SIZE = { 640,480 };
const static sf::Vector2f SCALE_INCREASE = { 0.005f,0.001f };
const static sf::Vector2f STEP_DISTANCE = { 2.0f, 3.0f };
const static sf::Vector2f SHAPE_SIZE = { 40.f, 20.f };

const static int ROTATION_SLOW = 2;
const static int ROTATION_FAST = 5;
const static int N_BLOCKS = 5;  //quantity of blocks
const static int RIGHT_X = 580;
const static int DOWN_Y = 370;
const static float MAX_SCALE = 1.9f;

const static int TIME_PER_FRAME = 15;  //as milliSeconds
