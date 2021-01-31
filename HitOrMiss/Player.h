#pragma once
#include <SFML/Graphics.hpp>
#include "Bomb.h"
class Player
{
public:
	Player(std::string filename, sf::Vector2f initPostion, float movementSpeed, bool isFaceingLeft = false);
	void handle_movement();
	void handle_event(sf::Event);
	void update();
	void handle_turns(int* turn);
	bool isWin(Player p);
	sf::Sprite getSprite();
	void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default);
private:
	sf::Texture m_player_texture;
	sf::Texture m_arrow_texture;
	sf::Sprite m_player_sprite;
	sf::Sprite m_arrow_sprite;
	float m_movement_speed;
	float m_angle;
	float m_power;
	bool m_is_aiming;
	sf::Clock m_aim_timer;
	Bomb m_bomb;
};

