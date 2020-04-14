#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI (3.14159265)
#define GRAVITY (500.0f)
float getAngle(float rotation)
{
	if (rotation < 0) return 0;
	if (rotation <= 180) return 180;
	return 360 - rotation;
}
sf::Vector2f getBombVelocity(float v0, float angle, float dt)
{
	double vx = v0 * cos(angle * PI / 180.0);
	double vy = v0 * sin(angle * PI / 180.0) - GRAVITY * dt;
	if(angle > 90 || angle == 180)
		return sf::Vector2f(-vx, vy);
	return sf::Vector2f(vx, vy);
}
sf::Vector2f getBombPos(float x0, float y0, float v, float angle, float dt)
{
	sf::Vector2f vt = getBombVelocity(v, angle, dt);
	double x = x0 + vt.x * cos(angle * PI / 180.0) * dt;
	double y = y0 + (-vt.y * sin(angle * PI / 180.0) * dt) + (0.5 * GRAVITY * dt * dt);	
	return sf::Vector2f(x, y);
}
int main()
{
	//textures:
	sf::Texture backgroundT;
	if (!backgroundT.loadFromFile("background3.jpg")) //load picture
		return EXIT_FAILURE;
	sf::Texture p1tRight; //create texture for player1
	if (!p1tRight.loadFromFile("p1-right.png")) //load picture
		return EXIT_FAILURE;
	sf::Texture p1tLeft; //create texture for player1
	if (!p1tLeft.loadFromFile("p1-left.png")) //load picture
		return EXIT_FAILURE;
	sf::Texture p2tLeft; //create texture for player2
	if (!p2tLeft.loadFromFile("p2-Left.png")) //load picture
		return EXIT_FAILURE;
	sf::Texture p2tRight; //create texture for player2
	if (!p2tRight.loadFromFile("p2-Right.png")) //load picture
		return EXIT_FAILURE;
	sf::Texture bombT;
	if (!bombT.loadFromFile("bomb1.png")) //load picture
		return EXIT_FAILURE;
	sf::Texture arrowT;
	if (!arrowT.loadFromFile("Arrow.png")) //load picture
		return EXIT_FAILURE;

	//sprites:
	sf::Sprite background(backgroundT);
	sf::Sprite p1(p1tRight); //insert to sprite player1
	sf::Sprite p2(p2tLeft);
	sf::Sprite bomb(bombT);
	sf::Sprite arrow(arrowT);

	//sizes:
	const int HEIGHT = backgroundT.getSize().y;
	const int WIDTH = backgroundT.getSize().x;
	const int GROUND = HEIGHT - p1.getTexture()->getSize().y - 50;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "HitOrMiss"); //creat window

	//initiate positions:
	background.setPosition(0, 0);
	p1.setPosition(0, GROUND);

	p2.setPosition(WIDTH- p2.getTexture()->getSize().x,GROUND);
	bomb.setOrigin(bombT.getSize().x / 2, bombT.getSize().y / 2);
	window.setFramerateLimit(60);
	arrow.setOrigin(0, arrowT.getSize().y / 2);
	arrow.setRotation(270);

	//the game loop:
	float move = 5.0f;
	double angle = 0;
	bool isAiming = false;
	bool isFiring = false;
	sf::Clock clock;
	clock.restart();
	window.setKeyRepeatEnabled(false);
	sf::Vector2f bombStartPosition;
	float power = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (!isFiring)
					{
						isAiming = true;
					}
				}
			}
			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (!isFiring)
					{
						power = arrow.getScale().x * 500;
						bombStartPosition = sf::Vector2f(p1.getPosition().x + p1tRight.getSize().x, p1.getPosition().y);
						isFiring = true;
						clock.restart();
						isAiming = false;
						arrow.setScale(1, 1);
					}
				}
			}
		}

		arrow.setPosition(p1.getPosition().x + p1tRight.getSize().x, p1.getPosition().y);

		//movements:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //player 1 move right
		{
			p1.setTexture(p1tRight);
			p1.move(sf::Vector2f(move, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			p1.setTexture(p1tLeft);
			p1.move(sf::Vector2f(-move, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (!isFiring)
			{
				if(arrow.getRotation() > 180)
					arrow.rotate(-1);
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (!isFiring)
			{
				if (arrow.getRotation() < 359)
					arrow.rotate(1);
			}
		}
		if (isAiming)
		{
			if (arrow.getScale().x < 3)
				arrow.scale(1.01, 1);
		}
		
		sf::Vector2f bomb_pos;
		if (isFiring)
		{
			float angle = getAngle(arrow.getRotation());
			bomb_pos = getBombPos(bombStartPosition.x, bombStartPosition.y, power, angle, clock.getElapsedTime().asSeconds());
			bomb.setPosition(bomb_pos);
		}
		if (bomb_pos.y > HEIGHT)
		{
			bomb.setPosition(-1000,-1000);
			isFiring = false;
		}

		//draw and display the sprites
		window.draw(background);
		if (isFiring)
			window.draw(bomb);
		window.draw(arrow);
		window.draw(p1);
		window.draw(p2);
		window.display();
	}

	return 0;
}