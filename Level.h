#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>
#include "Error.h"
#include "Track.h"
#include "Wave.h"

class Level : public GraphicsEntity
{
private:
	std::vector<Track> m_tracks;
	std::vector<Wave> m_waves;
	void skipChars(std::ifstream& inf) const;
public:
	Level(const sf::RenderWindow& window, const std::string& textureFile, const std::string& trackTextureFile, const std::string& trackDataFile);
	int load(const sf::RenderWindow& window, const std::string& trackTextureFile, const std::string& trackDataFile);
	const std::vector<Track>& getTracks() const { return m_tracks; }
	std::vector<Wave>& getWaves() { return m_waves; }
	sf::Vector2u getSize() const { return m_texture.getSize(); }
};

