#pragma once

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

int map[26][18] = { Color::CLEAR };

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

void decMap()
{
	int count = 0;
	for (int h = 26; h > 0; --h)
	{
		for (int w = 0; w < 18; ++w)
		{
			if (map[h][w] > 0) ++count;
		}

		if (count == 18)
		{
			for (int z = h; z > 0; --z)
				for (int w = 0; w < 18; ++w)
				{
					if (map[z][w] > 0)
					{
						map[z][w] = Color::CLEAR;
						map[z][w] = map[z - 1][w];
					}
				}
		}

		count = 0;
	}
}

void drawMap(sf::RenderWindow& window, sf::Sprite& spr_map)
{
	int size = 18;

	for(int h = 26; h > 0; --h)
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
				spr_map.setTextureRect(sf::IntRect(0, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case MAGENTA:
			{
				spr_map.setTextureRect(sf::IntRect(size, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case RED:
			{
				spr_map.setTextureRect(sf::IntRect(size * 2, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case GREEN:
			{
				spr_map.setTextureRect(sf::IntRect(size * 3, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case YELLOW:
			{
				spr_map.setTextureRect(sf::IntRect(size * 4, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case BLUE:
			{
				spr_map.setTextureRect(sf::IntRect(size * 5, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;

			case ORANGE:
			{
				spr_map.setTextureRect(sf::IntRect(size * 6, 0, size, size));
				spr_map.setPosition(w * 18, h * 18);
				window.draw(spr_map);
			}break;
			}
		}
}