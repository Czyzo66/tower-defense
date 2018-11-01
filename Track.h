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
	int loadFirstPointCoords(const sf::Color color);
public:
	//TODO: check if loading can be done better or without pointers
	int loadTrack(const std::string & trackTextureFile, const sf::Color color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords);
	bool empty() const;
	void rescale(sf::Vector2f screenRes);
	void rescale(sf::Vector2u screenRes);
	void rescale(float resX, float resY);
	void rescale(sf::RenderTarget&);
	sf::Vector2f back() const;
	sf::Vector2f front() const;
	std::vector<sf::Vector2f>::iterator begin();
	std::vector<sf::Vector2f>::iterator erase(std::vector<sf::Vector2f>::iterator itr);
};