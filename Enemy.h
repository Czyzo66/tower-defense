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
#include "GraphicsEntity.h"
#include "Track.h"
#include "EnemyProperties.h"

/*
 *	TODO:
 *		Every enemy has its own texture loaded into memory, but enemies of the same type use the same texture.
 *		Hence some textures in memory are redundant, enemies of the same type should share one texture.
 *		One solution is to make some Resource Manager class, other possibility may be to use shared pointer.
 *
 *		Enemy movement is not smooth, maybe it need to be redesigned.
  */

class Enemy : public GraphicsEntity
{
private:
	static std::map<int, EnemyProperties> s_enemyProperties;
	sf::Clock m_clock;
	sf::Vector2f m_size;
	const Track* m_trackPtr;
	int m_trackCounter;
	bool m_active;
	int m_state;
	int m_id;
	double m_hp;
	double m_speed;
	void init();
public:	
	Enemy(const int id, const Track* trackPtr);
	enum State
	{
		STATE_LEFT,
		STATE_MID,
		STATE_RIGHT,
		STATE_REACHED_END,
		STATE_ERROR_LOADING_TRACK,
	};	
	void resetTimer();
	void move();
	void setTrack(const Track* track);
	void setActive(bool ac) { m_active = ac; }	
	bool isActive() const { return m_active; }
	double getSpeed() const { return m_speed; }
	const Track& getTrack() const { return *m_trackPtr; }
	virtual ~Enemy() {}
};

