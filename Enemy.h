#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Error.h"
#include "Track.h"

/*
 *	TODO:
 *	move(): perhaps function should be simpler/faster
 */

class Enemy : public sf::Drawable
{
private:
	sf::Clock m_clock;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	Track m_track;
	bool m_active;
	int m_state;
	int m_hp;
	double m_speed;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Enemy(int hp, double speed) : m_hp(hp), m_speed(speed), m_position(sf::Vector2f(0, 0)), m_state(0), m_active(false) {}
	enum State
	{
		STATE_LEFT,
		STATE_MID,
		STATE_RIGHT,
	};
	int load(const std::string& textureFile, sf::Vector2f enemySize);
	void setTrack(Track& track);
	void setPosition(sf::Vector2f position);
	bool move();
	void setActive(bool ac) { m_active = ac; };
	bool isActive() const { return m_active; };
	double getSpeed() const { return m_speed; };
	void resetTimer();
};