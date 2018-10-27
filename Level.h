#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>
//#include <SFML/Audio.hpp> //no music for now
#include <string>
#include <vector>
#include <cmath>
#include "Error.h"

class Level : public sf::Drawable
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_startCoords;
	std::vector<sf::Vector2f> m_track;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int load(const std::string& textureFile);
	bool setTrack(std::vector<sf::Vector2f>& track);
	std::vector<sf::Vector2f>& getTrack() { return m_track; }
	sf::Vector2u getSize() { return m_texture.getSize(); }
	sf::Vector2f getStartCoords() { return m_startCoords; }
	bool setScale(sf::Vector2f scale);	
};

