#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Error.h"
#include "Track.h"

class Level : public sf::Drawable
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_startCoords;
	sf::Vector2f m_endCoords;
	Track m_track;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int load(const std::string& textureFile, const std::string& trackTextureFile);
	Track& getTrack() { return m_track; }
	sf::Vector2u getSize() { return m_texture.getSize(); }
	sf::Vector2f getStartCoords() { return m_startCoords; }
	bool setScale(sf::Vector2f scale);	
};

