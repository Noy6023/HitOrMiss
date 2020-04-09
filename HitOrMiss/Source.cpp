#include <cstdio>
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI (3.14159265)
#define GRAVITY (500.0f)
#define MASS (1)
//#define XFORCE (10)
#define YFORCE (0)
#define V0 (500.0f)
#define ANGLE (70.0f)
sf::Vector2f getAcceleration(float angle)
{
	//double x = (MASS * GRAVITY * cos(angle * PI / 180.0) + XFORCE * cos(angle * PI / 180.0)) / MASS;
	double y = (MASS * GRAVITY * cos(angle * PI / 180.0) + YFORCE * cos(angle * PI / 180.0)) / MASS;
	return sf::Vector2f(0, y);
}
sf::Vector2f getBombVelocity(float v0, float angle, float dt)
{
	//float ax = getAcceleration(angle).x;
	float ay = getAcceleration(angle).y;
	float ax = 0;
	//float ay = 0;
	double vx = v0 * cos(angle * PI / 180.0) + ax * dt;
	double vy = v0 * sin(angle * PI / 180.0) - ay * dt;
	return sf::Vector2f(vx, vy);
}
sf::Vector2f getBombPos(float x0, float y0, float v, float angle, float dt)
{
	//float ax = getAcceleration(angle).x;
	float ay = getAcceleration(angle).y;
	float ax = 0;
	sf::Vector2f vt = getBombVelocity(v, angle, dt);
	double x = x0 + vt.x * cos(angle * PI / 180.0) * dt + 0.5 * ax * dt * dt;
	double y = y0 + (-vt.y * sin(angle * PI / 180.0) * dt) + (0.5 * ay * dt * dt);
	printf("%f, %f", vt.x, vt.y);
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
	const int LENGTH = backgroundT.getSize().y;
	const int WIDTH = backgroundT.getSize().x;
	const int GROUND = LENGTH - p1.getTexture()->getSize().y - 50;

	sf::RenderWindow window(sf::VideoMode(WIDTH, LENGTH), "HitOrMiss"); //creat window
	//initiate positions:
	background.setPosition(0, 0);
	p1.setPosition(0, GROUND);

	p2.setPosition(WIDTH- p2.getTexture()->getSize().x,GROUND);
	bomb.setOrigin(bombT.getSize().x / 2, bombT.getSize().y / 2);
	//bomb.setScale(sf::Vector2f(2.0f, 2.0f));
	bomb.setPosition(100,100);
	window.setFramerateLimit(60);
	//the game loop:
	float move = 5.0f;
	double angle = 0;
	bool isAiming = false;
	sf::Clock clock;
	clock.restart();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

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
			p2.setTexture(p2tLeft);
			p2.move(sf::Vector2f(-move, 0));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			p2.setTexture(p2tRight);
			p2.move(sf::Vector2f(move, 0));
		}
		 
		sf::Vector2f bomb_pos = getBombPos(p1.getPosition().x + p1tRight.getSize().x, p1.getPosition().y, V0, ANGLE, clock.getElapsedTime().asSeconds());
		printf("%f\n", clock.getElapsedTime().asSeconds());
		printf("(%f, %f)\n", bomb_pos.x, bomb_pos.y);
		if(bomb_pos.y < 535)
			bomb.setPosition(bomb_pos);
		if (bomb.getPosition() == p2.getPosition()) printf("P1 has won!!!");
		//draw and display the sprites
		window.draw(background);
		window.draw(bomb);
		if (isAiming)
		{
			window.draw(arrow);
		}
		window.draw(p1);
		window.draw(p2);
		window.display();
	}

	return 0;
}

/*
#define PI (3.14159265)
#define GRAVITY (100.0f)
#define MASS (10)
#define XFORCE (10)
#define YFORCE (10)
sf::Vector2f getAcceleration(float angle)
{
	double x = (MASS * GRAVITY * cos(angle * PI / 180.0) + XFORCE * cos(angle * PI / 180.0)) / MASS;
	double y = (MASS * GRAVITY * cos(angle * PI / 180.0) + YFORCE * cos(angle * PI / 180.0)) / MASS;
	return sf::Vector2f(x, y);
}
sf::Vector2f getBombVelocity(float v0, float angle, float dt)
{
	float ax = getAcceleration(angle).x;
	float ay = getAcceleration(angle).y;
	//float ax = 0;
	double vx = v0 * cos(angle * PI / 180.0) + ax * dt;
	double vy = v0 * sin(angle * PI / 180.0) - GRAVITY * dt;
	return sf::Vector2f(vx, vy);
}
sf::Vector2f getBombPos(float x0, float y0, float v, float angle, float dt)
{
	float ax = getAcceleration(angle).x;
	float ay = getAcceleration(angle).y;
	//float ax = 0;
	sf::Vector2f vt = getBombVelocity(v, angle, dt);
	double x = x0 + vt.x * cos(angle * PI / 180.0) * dt + 0.5 * ax * dt *dt;
	double y = y0 + (-vt.y * sin(angle * PI / 180.0) * dt )+ (0.5 * GRAVITY * dt * dt);
	printf("%f, %f", vt.x, vt.y);
	return sf::Vector2f(x, y);
}
*/

/*
sf::Vector2f getBombPos(float x0, float y0, float v0, float angle, float t)
{
	double x = x0 + v0 * cos(angle * PI / 180.0) * t;
	double y = y0 + (-v0 * sin(angle * PI / 180.0) * t )+ (0.5 * GRAVITY * t * t);

	return sf::Vector2f(x, y);
}
*/