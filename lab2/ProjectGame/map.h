#pragma once
#include "game.h"

const static int WIDTH = 640;
const static int HEIGHT = 480;
const static int STEP = 32;

const static sf::String TILEMAP[HEIGHT / STEP] =
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