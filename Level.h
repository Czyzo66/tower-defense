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

class Level : public sf::Drawable
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::vector<Track> m_tracks;
	Track m_track;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void skipChars(std::ifstream& inf);
public:
	int load(sf::RenderWindow& window, const std::string& textureFile, const std::string& trackTextureFile, const std::string& trackDataFile);
	Track& getTrack() { return m_track; }
	const std::vector<Track> getTracks() const { return m_tracks; }
	const sf::Vector2u getSize() const { return m_texture.getSize(); }
	bool setScale(sf::Vector2f scale);	
};

