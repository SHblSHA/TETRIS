#ifndef MAP
#define MAP
#include <SFML/Graphics.hpp>
#include "const.h"
#include <Windows.h>
#include <iostream>

enum Color
{
	CLEAR,
	CYAN,
	MAGENTA,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	ORANGE,
};

__declspec(selectany)int map[26][18];

void drawLines(sf::RenderWindow& window);

void resetMap();

bool isNotAlive();

int decMap1();

void decMap2(int h);

void drawMap(sf::RenderWindow& window, sf::Sprite& spr_map, int height, bool& eq);
#endif