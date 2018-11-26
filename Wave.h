#pragma once
#include <SFML/System/Time.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "Error.h"
#include "Enemy.h"

/*
 *	TODO:
 *		Enemies shouldn't be activated all at the same time, because their sprites are overlapping.
 */

class Wave : public sf::Drawable
{
private:
	std::vector<Enemy> m_enemies;
	sf::Time m_startTime;
	bool m_active;
	void skipChars(std::ifstream& inf) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	Wave(std::ifstream & inf, std::vector<Track>* ptrTracks) : m_active(false) { loadFromFile(inf, ptrTracks); }
	int loadFromFile(std::ifstream& inf, std::vector<Track>* ptrTracks);
	const std::vector<Enemy>& getEnemies() const { return m_enemies; }
	void release(sf::Clock& clock);
};

