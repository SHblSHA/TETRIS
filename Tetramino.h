#ifndef TETRAMINO
#define TETRAMINO

#include <cmath>
#include <ctime>
#include "map.h"
#include <array>

int getRandomNumber(int min, int max);

class Point
{
public:
	int x;
	int y;
};

enum Dir
{
	LEFT,
	RIGHT,
	DEFAULT,
};

class Tetramino
{
private:
	static const int num = 4;
	static const int size = 18;
	Point point[num];
	static std::array<std::array<int, 4>, 7> tetramino;
	int type, spawnX, spawnY = -4;
	Color color;
	Dir m_dir;
	bool rot;
public:

	void setSpawnCoordinate();

	void spawn();

	void draw(sf::RenderWindow& window, sf::Sprite& spr_tetramino);

	void move();

	void interactionMap();

	void rotation();

	void setDir(Dir&& dir);

	void defaultMove(bool game, float time, float& delay, int level);

	const Dir& getDir();
};


#endif