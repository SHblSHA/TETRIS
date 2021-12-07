#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cassert>
#include <iostream>
#include "map.h"
#include <array>
#include <Windows.h>

int getRandomNumber(int min, int max)
{
	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
	return static_cast<int>(rand() * fraction * (max - min + 1) + min);
}

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
	DOWN,
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

	void setSpawnCoordinate()
	{
		for (int i = 0; i < 4; ++i)
		{
			point[i].x = (tetramino[type][i] % 2 + spawnX) * size;
			point[i].y = (tetramino[type][i] / 2 + spawnY) * size;
		}
	}

	void spawn()
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

	void draw(sf::RenderWindow& window, sf::Sprite& spr_tetramino)
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

	void move()
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
		case DOWN:
		{
			for (int i = 0; i < num; ++i)
			{
				point[i].y += size;
			}
		}break;
		}
	}

	void interactionMap()
	{
		for (int z = 0; z < num; ++z)
		{
			if (point[z].y == 468)
			{
				for (int i = 0; i < num; ++i)
					map[point[i].y / size][point[i].x / size] = color;
				spawn();
				return;
			}

			if (map[point[z].y / size + 1][point[z].x / size] > 0)
			{
				for (int i = 0; i < num; ++i)
					map[point[i].y / size][point[i].x / size] = color;

				spawn();
				return;
			}

			if (((map[point[z].y / size][point[z].x / size + 1] || point[z].x / size == 17) && m_dir == Dir::RIGHT) || ((map[point[z].y / size][point[z].x / size - 1] || point[z].x / size == 0) && m_dir == Dir::LEFT))
			{
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

	void rotation()
	{
		for (int i = 0; i < num; ++i)
		{
			int x = point[i].y - point[1].y;
			int y = point[i].x - point[1].x;
			point[i].x = point[1].x - x;
			point[i].y = point[1].y + y;
		}
	}

	void setDir(Dir&& dir)
	{
		m_dir = dir;
	}

	const Dir& getDir()
	{
		return m_dir;
	}
};

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

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();

	ShowWindow(GetConsoleWindow(), SW_HIDE);

	int h = 486;
	int w = 324;

	sf::RenderWindow window(sf::VideoMode(w, h), "TETRIS");

	sf::Font font;
	font.loadFromFile("resources/CyrilicOld.TTF");
	sf::Text text("YOU LOSE", font, 30);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(5);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(90, 200);

	sf::RectangleShape lineY(sf::Vector2f(h, 0.5f));
	lineY.setFillColor(sf::Color::Black);
	lineY.setRotation(90);

	sf::RectangleShape lineX(sf::Vector2f(w, 0.5f));
	lineX.setFillColor(sf::Color::Black);

	sf::RectangleShape line(sf::Vector2f(w, 2));
	line.setFillColor(sf::Color::Red);
	line.setPosition(0, 18 * 10);

	sf::Texture backGroundTexture;
	backGroundTexture.loadFromFile("resources/TufboJ.jpg ");
	sf::Sprite backGround(backGroundTexture);
	backGround.setScale(0.45f, 0.48f);

	Tetramino tetramino;
	tetramino.spawn();

	sf::Texture t;
	t.loadFromFile("resources/tiles.png");
	sf::Sprite spr_tetramino(t);

	sf::Sprite spr_map(t);

	bool keyPressed = 0;
	bool game = 1;

	sf::Clock clock;

	float delay = 0;
	float timerMove = 0;
	float rotateTimer = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;

		sf::Event event;

		timerMove += time;
		rotateTimer += time;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (game)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if ((event.key.code == sf::Keyboard::Right) && timerMove > 100)
					{
						tetramino.setDir(Dir::RIGHT);
						tetramino.interactionMap();
						tetramino.move();
						timerMove = 0;
					}

					if ((event.key.code == sf::Keyboard::Down) && timerMove > 25)
					{
						tetramino.setDir(Dir::DOWN);
						tetramino.move();
						timerMove = 0;
					}

					if (event.key.code == sf::Keyboard::Up && rotateTimer > 200)
					{
						tetramino.setDir(Dir::DEFAULT);
						tetramino.rotation();
						rotateTimer = 0;
					}

					if ((event.key.code == sf::Keyboard::Left) && timerMove > 100)
					{
						tetramino.setDir(Dir::LEFT);
						tetramino.interactionMap();
						tetramino.move();
						timerMove = 0;
					}
				}

				if (event.type == sf::Event::KeyReleased)
				{
					if (event.key.code == sf::Keyboard::Down)
					{
						tetramino.setDir(Dir::DEFAULT);
					}
				}
			}
		}

		window.draw(backGround);

		for (int i = 1; i < 18; ++i)
		{
			lineY.setPosition(i * 18, 0);
			window.draw(lineY);
		}

		for (int i = 0; i < 27; ++i)
		{
			if (i == 10) continue;
			lineX.setPosition(0, i * 18);
			window.draw(lineX);
		}

		window.draw(line);

		if ((tetramino.getDir() != Dir::DOWN) && game)
		{
			delay += time;
		}
		if (delay > 300)
		{
			tetramino.setDir(Dir::DEFAULT);
			tetramino.move();
			delay = 0;
		}

		tetramino.interactionMap();
		tetramino.draw(window, spr_map);

		decMap();
		drawMap(window, spr_map);

		if (isNotAlive())
		{
			game = false;
			window.draw(text);
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				game = true;
				resetMap();
			}
		}

		window.display();
	}
	return 0;
}