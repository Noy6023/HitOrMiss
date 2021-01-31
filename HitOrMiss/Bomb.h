#pragma once
#include <SFML/Graphics.hpp>
class Bomb
{
public:
	Bomb(sf::Vector2f m_min_hit, sf::Vector2f m_max_hit);
	//~Bomb();
	void shoot(sf::Vector2f initPosition, float angle, float power);
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
	bool get_m_is_firing();
	int get_m_stage();
	bool hasHit();
	void update();
	void set_hits(sf::Vector2f min, sf::Vector2f max);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_init_position;
	sf::Clock m_timer;
	float m_angle;
	float m_power;
	bool m_is_firing;
	int m_stage;
	sf::Vector2f m_min_hit;
	sf::Vector2f m_max_hit;
};

