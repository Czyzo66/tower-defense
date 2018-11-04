#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Error.h"

class Track
{
private:
	std::vector<sf::Vector2f> m_track;
	sf::Image m_trackTexture;
	sf::Vector2f m_lastFoundCoords;
	sf::Vector2f m_secondLastFoundCoords;
	int loadFirstPointCoords(const sf::Color color);
	void save(sf::Vector2f& point);
	void saveAndPush(sf::Vector2f& point);
public:
	int loadTrack(const std::string & trackTextureFile, const sf::Color color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords);
	bool empty() const;
	void rescale(sf::Vector2f screenRes);
	void rescale(sf::Vector2u screenRes);
	void rescale(float resX, float resY);
	void rescale(sf::RenderTarget&);
	sf::Vector2f& back();
	sf::Vector2f& front();
	std::vector<sf::Vector2f>::iterator begin();
	std::vector<sf::Vector2f>::iterator end();
	std::vector<sf::Vector2f>::iterator erase(std::vector<sf::Vector2f>::iterator itr);
	void pop_back();
};