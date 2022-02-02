#include "Tetramino.h"
#include <Windows.h>
#include <iostream>
#include <string>

int main()
{
	srand(static_cast<unsigned int>(time(0)));

	ShowWindow(GetConsoleWindow(), SW_NORMAL);

	sf::RenderWindow window(sf::VideoMode(w, h), "TETRIS");
	
	sf::Font font;
	font.loadFromFile("resources/CyrilicOld.TTF");
	sf::Text text("YOU LOSE", font, 30);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(5);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(80, 200);

	sf::Text xpText("", font, 30);
	xpText.setFillColor(sf::Color(117, 187, 253));
	xpText.setOutlineThickness(5);
	xpText.setOutlineColor(sf::Color::Black);
	xpText.setPosition(280, 5);

	int xp = 0;
	int level = 0;

	sf::Texture backGroundTexture;
	backGroundTexture.loadFromFile("resources/TufboJ.jpg ");
	sf::Sprite backGround(backGroundTexture);
	backGround.setScale(0.45f, 0.48f);

	Tetramino tetramino;
	tetramino.spawn();

	sf::Texture t;
	t.loadFromFile("resources/tiles.png");
	sf::Sprite spr_tetramino(t);

	bool game = true;
	bool eq = false;
	bool buff = true;

	sf::Clock clock;

	float delay = 0;
	float timerMove = 0;
	float rotateTimer = 0;
	float newLevelTimer = 0;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;

		sf::Event event;

		timerMove += time;
		rotateTimer += time;
		newLevelTimer += time;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (game)
			{
				if (event.type == sf::Event::KeyPressed)
				{
					if ((event.key.code == sf::Keyboard::Right) && timerMove > 50 - 5 * level)
					{
						tetramino.setDir(Dir::RIGHT);
						tetramino.interactionMap();
						tetramino.move();
						timerMove = 0;
					}

					if ((event.key.code == sf::Keyboard::Down) && timerMove > 25)
					{
						tetramino.setDir(Dir::DEFAULT);
						tetramino.move();
						timerMove = 0;
					}

					if (event.key.code == sf::Keyboard::Up && rotateTimer > 125)
					{
						tetramino.setDir(Dir::DEFAULT);
						tetramino.rotation();
						rotateTimer = 0;
					}

					if ((event.key.code == sf::Keyboard::Left) && timerMove > 50 - 5 * level)
					{
						tetramino.setDir(Dir::LEFT);
						tetramino.interactionMap();
						tetramino.move();
						timerMove = 0;
					}
				}
			}
		}

		window.draw(backGround);

		drawLines(window);

		tetramino.defaultMove(game, time, delay, level);

		tetramino.interactionMap();
		tetramino.draw(window, spr_tetramino);

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

		xpText.setString(std::to_string(xp));
		window.draw(xpText);

		if (!(xp % 10) && newLevelTimer < 1000)
		{
			if (buff)
			{
				++level;
				buff = false;
			}
			text.setString("NEW LEVEL");
			window.draw(text);
			text.setString("YOU LOSE");
		}

		int h = decMap1();

		drawMap(window, spr_tetramino, h, eq);

		window.display();
		if (eq)
		{
			newLevelTimer = 0;
			xp += 10;
			buff = true;
			eq = false;
			Sleep(300);
		}
		decMap2(h);

	}
	return 0;
}