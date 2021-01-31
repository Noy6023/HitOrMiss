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
	sf::Texture explosionTexture;
	if (!explosionTexture.loadFromFile("Resources/explosion.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite explosion(explosionTexture);
	explosion.setOrigin(sf::Vector2f(explosionTexture.getSize().x / 2, explosionTexture.getSize().y / 2));
	const int HEIGHT = backgroundTexture.getSize().y;
	const int WIDTH = backgroundTexture.getSize().x;
	background.setPosition(0, 0);
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HitOrMiss");
	window.setFramerateLimit(60);
	Player players[2] = { Player("Resources/p1.png", sf::Vector2f(200,550), 5.0f),
						Player("Resources/p2.png", sf::Vector2f(800,550), 5.0f, true)};
	int turn = 0;
	int won = -1;
	int lost = 0;
	//the game loop:
	window.setKeyRepeatEnabled(false);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			players[turn%2].handle_event(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		players[turn%2].handle_movement();
		for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
		{
			players[i].update();
			if (i == 0)
			{
				if (players[i].isWin(players[i+1]))
				{
					won = i;
				}
			}
			else if (players[i].isWin(players[i - 1]))
			{
				won = i;
			}
		}
		if (won == 1) lost = 0;
		if (won == 0) lost = 1;
		//draw and display the sprites
		window.draw(background);
		for (int i = 0; i < sizeof(players) / sizeof(Player); i++)
			players[i].draw(window);
		players[turn % 2].handle_turns(&turn);

		if (won != -1)
		{
			int temp = won + 1;
			printf("Player %d is the winner!!!\n ", won+1);
			explosion.setPosition(players[lost].getSprite().getPosition());
			window.draw(explosion);
		}
		window.display();
	}
	return 0;
}