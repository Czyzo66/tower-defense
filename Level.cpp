#include "Level.h"




void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

int Level::load(const std::string& textureFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_sprite.setTexture(m_texture);
	return 0;
}

bool Level::setTrack(std::vector<sf::Vector2f>& track)
{
	m_track = track; 
	m_startCoords = m_track[0];
	return true;
}

bool Level::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	return true;
}

