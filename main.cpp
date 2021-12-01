////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <array>
#include <iostream>
#include <utility>

class Point
{
public:
	int x;
	int y;
};

class Tetramino
{
private:
	Point point[4];
	static std::array<std::array<int, 4>, 7> tetramino;
	int type;
public:
	Tetramino()
	{
		spawn();
	}

	Tetramino(int x)
	{
		spawn(x);
	}

	void spawn(int x = 0)
	{
		int type = 5; // задаем тип тетрамино
		for (int i = 0; i < 4; i++)
		{
			point[i].x = tetramino[type][i] % 2 + x;
			point[i].y = tetramino[type][i] / 2;
		}
	}

	const Point* getPoint()
	{
		return point;
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

/////////////////////////////////поворот тетрамино x2 = x0 + (y0 - y1)  y2 = y0 - (x1 - x2)
int main()
{
	sf::RenderWindow window(sf::VideoMode(324, 486), "TETRIS");

	sf::RectangleShape lineY(sf::Vector2f(486.f, 0.5f));
	lineY.setFillColor(sf::Color::Black);
	lineY.setRotation(90);

	sf::RectangleShape lineX(sf::Vector2f(324.f, 0.5f));
	lineX.setFillColor(sf::Color::Black);

	sf::Texture map;
	map.loadFromFile("resources/TufboJ.jpg ");
	sf::Sprite backGround(map);
	backGround.setScale(0.42f, 0.47f);

	std::vector<Tetramino> tetramino;
	sf::Texture t;
	t.loadFromFile("resources/2.png");
	sf::Sprite spr_tetramino(t);

	bool b = 1;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//=======================ОТРИСОВКА КАРТЫ===============================
		window.draw(backGround);

		for (int i = 1; i < 18; ++i)
		{
			lineY.setPosition(i * 18, 0);
			window.draw(lineY);
		}

		for (int i = 0; i < 27; ++i)
		{
			lineX.setPosition(0, i * 18);
			window.draw(lineX);
		}

		if (b)
		{
			tetramino.push_back(Tetramino());
			tetramino.push_back(Tetramino(2));
			b = false;
		}

		///////////отрисовка тетрамино//////////
		for (int j = 0; j < tetramino.size(); ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				spr_tetramino.setTextureRect(sf::IntRect(0, 0, 18, 18));
				spr_tetramino.setPosition(tetramino[j].getPoint()[i].x * 18, tetramino[j].getPoint()[i].y * 18);
				window.draw(spr_tetramino);
			}
		}

		window.display();
	}
}

