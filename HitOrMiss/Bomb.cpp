#include "Bomb.h"
#include <stdio.h>


#define PI (3.14159265)
#define GRAVITY (500.0f)

Bomb::Bomb()
	:m_angle(0), m_power(0), m_is_firing(false)

{
	if (!m_texture.loadFromFile("Resources/Bomb.png"))
	{
		exit(1);
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, 0);
}

Bomb::~Bomb()
{
	printf("Bomb Destruced!\n");
}

sf::Vector2f getBombVelocity(float v0, float angle, float dt)
{
	double vx = v0 * cos(angle * PI / 180.0);
	double vy = v0 * sin(angle * PI / 180.0) - GRAVITY * dt;
	if (angle > 90 || angle == 180)
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

void Bomb::shoot(sf::Vector2f initPosition, float angle, float power)
{
	m_is_firing = true;
	//m_sprite.setPosition(initPosition);
	m_init_position = initPosition;
	m_angle = angle;
	m_power = power;
	m_timer.restart();
}

void Bomb::update()
{
	sf::Vector2f bomb_pos = getBombPos(m_init_position.x, m_init_position.y, m_power, m_angle, m_timer.getElapsedTime().asSeconds());
	m_sprite.setPosition(bomb_pos);
	if (bomb_pos.y > 550)
	{
		m_is_firing = false;
	}
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (m_is_firing)
		target.draw(m_sprite);
}
