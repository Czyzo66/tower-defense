#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cassert>
#include "Error.h"
#include "Track.h"
#include "EnemyProperties.h"

/*
 *	TODO:
 *	move(): perhaps function should be simpler/faster
 */

class Enemy : public sf::Drawable
{
private:
	static std::map<int, EnemyProperties> s_enemyProperties;
	sf::Clock m_clock;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	Track m_track;
	bool m_active;
	int m_state;
	double m_hp;
	double m_speed;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:	
	Enemy(const int id);
	enum State
	{
		STATE_LEFT,
		STATE_MID,
		STATE_RIGHT,
	};
	int load(const std::string& textureFile);
	void setTrack(Track track);
	void setPosition(sf::Vector2f position);
	bool move();
	void setActive(bool ac) { m_active = ac; };
	const bool isActive() const { return m_active; };
	const double getSpeed() const { return m_speed; };
	const Track& getTrack() const { return m_track; };
	void resetTimer();
	virtual ~Enemy() {};
};

