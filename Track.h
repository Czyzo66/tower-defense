#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Error.h"

class Track
{
private:
	std::vector<sf::Vector2f> m_track;
	sf::Image m_trackTexture;
	sf::Vector2f m_lastFoundPoint;
	sf::Vector2f m_secondlastFoundPoint;
	void loadFirstPoint(const sf::Color& color);
	void loadRemainingPoints(const sf::Vector2f& startCoords, const sf::Color& color, const sf::Vector2u& textureSize);
	void loadOffscreenPoint(const sf::Vector2f& startOrEndCoords, const sf::Vector2u& textureSize);
	void save(const sf::Vector2f& point);
	void saveAndPush(const sf::Vector2f& point);
	void skipChars(std::ifstream& inf) const;
public:
	Track() {}
	Track(const std::string& trackTextureFile, const sf::Color& color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords);
	Track(std::ifstream& inf, const std::string& trackTextureFile);
	void loadTrack(const std::string& trackTextureFile, const sf::Color& color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords);
	void loadFromFile(std::ifstream& inf, const std::string& trackTextureFile);
	void rescale(const sf::Vector2f& screenRes);
	void rescale(const sf::Vector2u& screenRes);
	void rescale(const float resX, const float resY);
	void rescale(const sf::RenderTarget&);

	sf::Vector2f& operator[] (const int index) { return m_track[index]; }
	const sf::Vector2f& operator[] (const int index) const { return m_track[index]; }
	sf::Vector2f& at(const int index) { return m_track.at(index); }
	const sf::Vector2f& at(const int index) const { return m_track.at(index); }
	sf::Vector2f& back() { return m_track.back(); }
	const sf::Vector2f& back() const { return m_track.back(); }
	sf::Vector2f& front() { return m_track.front(); }
	const sf::Vector2f& front() const { return m_track.front(); }
	bool empty() const { return m_track.empty(); }
	std::vector<sf::Vector2f>::iterator begin() { return m_track.begin(); }
	std::vector<sf::Vector2f>::iterator end() { return m_track.end(); }
	void pop_back() { m_track.pop_back(); }
	size_t size() const { return m_track.size(); }
};