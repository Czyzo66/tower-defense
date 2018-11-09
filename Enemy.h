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

/*
 *	TODO:
 *	move(): perhaps function should be simpler/faster
 */

class Enemy : public sf::Drawable
{
private:
	static std::map<int, std::pair<double, double>> s_enemyProperties;//<Enemy Type, <Enemy HP, Enemy Speed>>
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
	Enemy(const int id) : m_hp(s_enemyProperties[id].first), m_speed(s_enemyProperties[id].second), m_position(sf::Vector2f(0, 0)), m_state(0), m_active(false) {}
	enum Type
	{
		//Enemy types may be changed
		TYPE_SLOW,	//0
		TYPE_FAST,	//1
	};
	enum State
	{
		STATE_LEFT,
		STATE_MID,
		STATE_RIGHT,
	};
	//static int loadProperties(const std::string& propsFile);
	int load(const std::string& textureFile, sf::Vector2f enemySize);
	void setTrack(Track& track);
	void setPosition(sf::Vector2f position);
	bool move();
	void setActive(bool ac) { m_active = ac; };
	bool isActive() const { return m_active; };
	double getSpeed() const { return m_speed; };
	void resetTimer();
};

