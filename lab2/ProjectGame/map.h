#pragma once
#include <SFML/Graphics.hpp>

//map resolution
const int WIDTH = 640;
const int HEIGHT = 480;

const int STEP = 32;  //blockSize (32x32)

const sf::String TILEMAP[HEIGHT / STEP] =
{
	"bbbbbbbbbbbbbbbbbbbb",
	"b                  b",
	"b                  b",
	"b   b   b  b   b   b",
	"b    b        b    b",
	"b        bb        b",
	"b                  b",
	"b bbbbb      bbbbb b",
	"b   b          b   b",
	"b      b    b      b",
	"b   b          b   b",
	"b bbbbb      bbbbb b",
	"b        bb        b",
	"b                  b",
	"bbbbbbbbbbbbbbbbbbbb",
};