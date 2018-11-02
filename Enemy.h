#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Error.h"
#include "Track.h"

/*
 *	TODO:
 *	Rework texture management (sprite.setTextureRect instead 3 separate sprites)
 *	Check Enemy::move for new track - movement speed may be too high on curves
 */

class Enemy : public sf::Drawable
{
private:
	sf::Clock m_clock;
	sf::Vector2f m_size;
	sf::Vector2f m_position;
	sf::Texture m_texture;
	sf::Sprite m_left;
	sf::Sprite m_mid;
	sf::Sprite m_right;
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
	//bool calculateTrack(std::vector<sf::Vector2f>& track, int targetX, int targetY, int textureX, int textureY);
	//bool calculateTrack(std::vector<sf::Vector2f>& track, sf::Vector2u targetSize, sf::Vector2u textureSize);
	void setTrack(Track& track);
	//bool setTrack(std::vector<sf::Vector2f>& track);
	bool setPosition(sf::Vector2f position);
	void move_test();	//TODO: remove?
	bool move();
	void setActive(bool ac) { m_active = ac; };
	bool getActive() const { return m_active; };
	void resetTimer();
};