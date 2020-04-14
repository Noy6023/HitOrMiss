#pragma once
#include <SFML/Graphics.hpp>
class Bomb
{
public:
	Bomb();
	~Bomb();
	void shoot(sf::Vector2f initPosition, float angle, float power);
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
	void update();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_init_position;
	sf::Clock m_timer;
	float m_angle;
	float m_power;
	bool m_is_firing;
};

