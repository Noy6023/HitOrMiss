#include "Player.h"
Player::Player(std::string filename, sf::Vector2f initPostion, float movementSpeed, bool isFaceingLeft)
	: m_movement_speed(movementSpeed), m_angle(0), m_power(0), m_is_aiming(false), m_bomb()
{
	if (!m_player_texture.loadFromFile(filename))
	{
		exit(1);
	}
	m_player_sprite.setTexture(m_player_texture);
	m_player_sprite.setOrigin(m_player_texture.getSize().x / 2, 0);
	m_player_sprite.setPosition(initPostion.x, initPostion.y- m_player_texture.getSize().y);
	if (isFaceingLeft)
		m_player_sprite.setScale(-1, 1);

	if (!m_arrow_texture.loadFromFile("Resources/arrow.png"))
	{
		exit(1);
	}
	m_arrow_sprite.setTexture(m_arrow_texture);
	m_arrow_sprite.setOrigin(0, m_arrow_texture.getSize().y / 2);
	m_arrow_sprite.setRotation(270);
	
}

float getAngle(float rotation)
{
	if (rotation < 0) return 0;
	if (rotation <= 180) return 180;
	return 360 - rotation;
}

void Player::handle_event(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_is_aiming = true;
			m_aim_timer.restart();
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
		{
			m_power = m_arrow_sprite.getScale().x * 500;
			m_angle = getAngle(m_arrow_sprite.getRotation());
			m_bomb.shoot(m_arrow_sprite.getPosition(), m_angle, m_power);
			m_aim_timer.restart();
			m_is_aiming = false;
			m_arrow_sprite.setScale(1, 1);
		}
	}
}

void Player::update()
{
	if (m_is_aiming)
	{
		if (m_arrow_sprite.getScale().x < 3)
			m_arrow_sprite.scale(1.01, 1);
	}
	m_bomb.update();
}

void Player::handle_turns(int* turn)
{
	if (m_bomb.get_m_is_firing())
		* turn = *turn + 1;
}

void Player::handle_movement()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_player_sprite.setScale(1, 1);
		m_player_sprite.move(sf::Vector2f(m_movement_speed, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_player_sprite.setScale(-1, 1);
		m_player_sprite.move(sf::Vector2f(-m_movement_speed, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(m_arrow_sprite.getRotation() > 180)
			m_arrow_sprite.rotate(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (m_arrow_sprite.getRotation() < 359)
			m_arrow_sprite.rotate(1);
	}
	m_arrow_sprite.setPosition(m_player_sprite.getPosition().x, m_player_sprite.getPosition().y - 5);
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states)
{
	target.draw(m_player_sprite);
	target.draw(m_arrow_sprite);
	m_bomb.draw(target);
}
