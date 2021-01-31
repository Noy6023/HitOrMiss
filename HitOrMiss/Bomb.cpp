#include "Bomb.h"
#include <stdio.h>


#define PI (3.14159265)
#define GRAVITY (500.0f)

Bomb::Bomb(sf::Vector2f min_hit, sf::Vector2f max_hit)
	:m_angle(0), m_power(0), m_is_firing(false), m_stage(0)

{
	if (!m_texture.loadFromFile("Resources/Bomb.png"))
	{
		exit(1);
	}
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_texture.getSize().x / 2, 0);
	m_min_hit.x = min_hit.x;
	m_min_hit.y = min_hit.y;
	m_max_hit.x = max_hit.x;
	m_max_hit.y = max_hit.y;
}

/*Bomb::~Bomb()
{
	printf("Bomb Destruced!\n");
}*/

sf::Vector2f getBombVelocity(float v0, float angle, float t)
{
	double vx = v0 * cos(angle * PI / 180.0);
	double vy = v0 * sin(angle * PI / 180.0) - (float)GRAVITY * t;
	if (angle > 90 || angle == 180)
		return sf::Vector2f(-vx, vy);
	return sf::Vector2f(vx, vy);
}
sf::Vector2f getBombPos(sf::Vector2f initPosition, float v, float angle, float t)
{
	sf::Vector2f vt = getBombVelocity(v, angle, t);
	double x = initPosition.x + vt.x * cos(angle * PI / 180.0) * t;
	double y = initPosition.y + (-vt.y * sin(angle * PI / 180.0) * t) + (0.5 * GRAVITY * t * t);
	return sf::Vector2f(x, y);
}

void Bomb::shoot(sf::Vector2f initPosition, float angle, float power)
{
	m_is_firing = true;
	m_stage = 0;
	m_init_position = initPosition;
	m_angle = angle;
	m_power = power;
	m_timer.restart();
}

void Bomb::update()
{
	m_stage = 1;
	sf::Vector2f bomb_pos = getBombPos(m_init_position, m_power, m_angle, m_timer.getElapsedTime().asSeconds());
	m_sprite.setPosition(bomb_pos);
	if (m_is_firing && bomb_pos.y > 560)
	{
		m_is_firing = false;
		m_stage = 3;
		m_sprite.setPosition(-500, -500);
	}
}

void Bomb::set_hits(sf::Vector2f min, sf::Vector2f max)
{
	m_min_hit = min;
	m_max_hit = max;
}

void Bomb::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if (m_is_firing)
		target.draw(m_sprite);
}

bool Bomb::get_m_is_firing()
{
	return m_is_firing;
}

int Bomb::get_m_stage()
{
	return m_stage;
}

bool Bomb::hasHit()
{
	if (m_sprite.getPosition().x > m_min_hit.x && m_sprite.getPosition().x < m_max_hit.x)
	{
		if (m_sprite.getPosition().y > m_min_hit.y && m_sprite.getPosition().y < m_max_hit.y)
			return true;
	}
	return false;
}
