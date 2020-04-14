#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Player.h"

int main()
{
	//setting:
	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("Resources/background.jpg")) //load picture
		return EXIT_FAILURE;

	sf::Sprite background(backgroundTexture);
	const int HEIGHT = backgroundTexture.getSize().y;
	const int WIDTH = backgroundTexture.getSize().x;
	background.setPosition(0, 0);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HitOrMiss");
	window.setFramerateLimit(60);

	Player players[2] = { Player("Resources/p1.png", sf::Vector2f(200,550), 5.0f),
						Player("Resources/p2.png", sf::Vector2f(800,550), 5.0f, true)};

	//the game loop:
	window.setKeyRepeatEnabled(false);
	while (window.isOpen())
	{
		for (int i = 0; i < 2; i++)
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				players[i].handle_event(event);

				if (event.type == sf::Event::Closed)
					window.close();
			}

			players[i].handle_movement();
			players[i].update();

			//draw and display the sprites
		}
		window.draw(background);
		for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
			players[i].draw(window);
		window.display();
	}

	return 0;
}

/*
//the game loop:
window.setKeyRepeatEnabled(false);
while (window.isOpen())
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
			players[i].handle_event(event);

		if (event.type == sf::Event::Closed)
			window.close();
	}

	for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
	{
		players[i].handle_movement();
		players[i].update();
	}

	//draw and display the sprites
	window.draw(background);
	for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
		players[i].draw(window);

	window.display();
return 0;
}*/