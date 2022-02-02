#include "map.h"

void resetMap()
{
	for (int h = 26; h > 0; --h)
		for (int w = 0; w < 18; ++w)
			map[h][w] = Color::CLEAR;
}

bool isNotAlive()
{
	for (int w = 0; w < 18; ++w)
		if (map[9][w])
		{
			return true;
		}

	return false;
}

int decMap1()
{
	int count = 0;
	for (int h = 26; h > 9; --h)
	{
		count = 0;
		for (int w = 0; w < 18; ++w)
		{
			if (map[h][w]) ++count;
		}

		if (count == 18) return h;
	}
	return -1;
}

void decMap2(int h)
{
	if (h == -1) return;
	for (int w = 0; w < 18; ++w)
	{
		for (int z = h; z > 9; --z)
		{
			if (map[z - 1][w])
			{
				map[z][w] = map[z - 1][w];
			}

			else map[z][w] = CLEAR;
		}
	}
}

void drawMap(sf::RenderWindow& window, sf::Sprite& spr_map, int height, bool& eq)
{
	for (int h = 26; h > 5; --h)
	{
		for (int w = 0; w < 18; ++w)
		{
			switch (map[h][w])
			{
			case CLEAR:
			{
				continue;
			}

			case CYAN:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(0, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case MAGENTA:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case RED:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size * 2, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case GREEN:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size * 3, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case YELLOW:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size * 4, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case BLUE:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size * 5, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;

			case ORANGE:
			{
				if (h == height)
				{
					spr_map.setColor(sf::Color::Red);
					eq = true;
				}
				spr_map.setTextureRect(sf::IntRect(size * 6, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
				spr_map.setColor(sf::Color::White);
			}break;
			}
		}
	}
}

void drawLines(sf::RenderWindow& window)
{
	sf::RectangleShape line;
	line.setFillColor(sf::Color::Black);

	line.setSize(sf::Vector2f(1, h));
	for (int i = 1; i < 18; ++i)
	{
		line.setPosition(i * 18, 0);
		window.draw(line);
	}

	line.setSize(sf::Vector2f(w, 1));
	for (int i = 0; i < 27; ++i)
	{
		if (i == 10)
		{
			line.setSize(sf::Vector2f(w, 2));
			line.setFillColor(sf::Color::Red);
			line.setPosition(0, i * 18);
			window.draw(line);
			line.setSize(sf::Vector2f(w, 1));
			line.setFillColor(sf::Color::Black);
			continue;
		}
		line.setPosition(0, i * 18);
		window.draw(line);
	}
}