#include "Tetramino.h"
#include <Windows.h>

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

std::array<std::array<int, 4>, 7> Tetramino::tetramino =
{
	1,3,5,7, 
	2,4,5,7, 
	3,5,4,6, 
	3,5,4,7,
	2,3,5,7, 
	3,5,7,6, 
	2,3,4,5,
};


void Tetramino::setDir(Dir&& dir)
{
	m_dir = dir;
}

const Dir& Tetramino::getDir()
{
	return m_dir;
}

void Tetramino::rotation()
{
	for (int i = 0; i < num; ++i)
	{
		int x = point[i].y - point[1].y;
		int y = point[i].x - point[1].x;
		point[i].x = point[1].x - x;
		point[i].y = point[1].y + y;
	}
}

void Tetramino::interactionMap()
{
	for (int z = 0; z < num; ++z)
	{
		if (point[z].y == 468)
		{
			for (int i = 0; i < num; ++i)
				map[point[i].y / size][point[i].x / size] = color;
			spawn();
			break;
		}

		if (map[point[z].y / size + 1][point[z].x / size] > 0)
		{
			for (int i = 0; i < num; ++i)
				map[point[i].y / size][point[i].x / size] = color;

			spawn();
			break;
		}

		if (((map[point[z].y / size][point[z].x / size + 1] || point[z].x / size == 17) && m_dir == Dir::RIGHT) || ((map[point[z].y / size][point[z].x / size - 1] || point[z].x / size == 0) && m_dir == Dir::LEFT))
		{
			Sleep(50);
			m_dir = Dir::DEFAULT;
			break;
		}

		if (point[z].x < 0)
		{
			for (int i = 0; i < num; ++i)
				point[i].x += size;
		}

		if (point[z].x > 306)
		{
			for (int i = 0; i < num; ++i)
				point[i].x -= size;
		}
	}
}

void Tetramino::move()
{
	switch (m_dir)
	{
	case LEFT:
	{
		for (int i = 0; i < num; ++i)
		{
			point[i].x -= size;
		}
	}break;

	case RIGHT:
	{
		for (int i = 0; i < num; ++i)
		{
			point[i].x += size;
		}
	}break;

	case DEFAULT:
	{
		for (int i = 0; i < num; ++i)
		{
			point[i].y += size;
		}
	}break;
	}
}

void Tetramino::setSpawnCoordinate()
{
	for (int i = 0; i < 4; ++i)
	{
		point[i].x = (tetramino[type][i] % 2 + spawnX) * size;
		point[i].y = (tetramino[type][i] / 2 + spawnY) * size;
	}
}

void Tetramino::spawn()
{
	type = getRandomNumber(0, 6);
	rot = static_cast<bool>(getRandomNumber(0, 1));
	color = static_cast<Color>(getRandomNumber(1, 7));

	if (rot)
	{
		switch (type)
		{
		case 0:
		case 2:
		case 3:
		case 5:
			spawnX = getRandomNumber(0, 15); break;
		case 4:
		case 6:
			spawnX = getRandomNumber(0, 16); break;
		case 1:
			spawnX = getRandomNumber(0, 14); break;
		}
		spawnY = -3;
		setSpawnCoordinate();
		rotation();
	}

	else
	{
		spawnX = getRandomNumber(0, 16);
		spawnY = -4;
		setSpawnCoordinate();
	}
}

void Tetramino::draw(sf::RenderWindow& window, sf::Sprite& spr_tetramino)
{
	for (int i = 0; i < 4; ++i)
	{
		switch (color)
		{
		case CYAN:
		{
			spr_tetramino.setTextureRect(sf::IntRect(0, 0, size, size));
		}break;

		case MAGENTA:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size, 0, size, size));
		}break;

		case RED:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size * 2, 0, size, size));
		}break;

		case GREEN:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size * 3, 0, size, size));
		}break;

		case YELLOW:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size * 4, 0, size, size));
		}break;

		case BLUE:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size * 5, 0, size, size));
		}break;

		case ORANGE:
		{
			spr_tetramino.setTextureRect(sf::IntRect(size * 6, 0, size, size));
		}break;
		}

		spr_tetramino.setPosition(point[i].x, point[i].y);
		window.draw(spr_tetramino);
	}
}

void Tetramino::defaultMove(bool game, float time, float& delay, int level)
{
	if (game) delay += time;
	if (delay > 300 - 25 * level)
	{
		this->setDir(Dir::DEFAULT);
		this->move();
		delay = 0;
	}
}