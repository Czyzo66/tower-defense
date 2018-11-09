#include "Level.h"




void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

int Level::load(sf::RenderWindow& window, const std::string& textureFile, const std::string& trackTextureFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(window.getSize().x / 1920, window.getSize().y / 1200);
	m_startCoords = sf::Vector2f(1919.0f, 450.0f);
	m_endCoords = sf::Vector2f(0.0f, 1037.0f);
	int ret = m_track.loadTrack(trackTextureFile, sf::Color(255, 0, 0), m_startCoords, m_endCoords);
	if (ret) return ret;
	m_track.rescale(window.getSize());
	return 0;
}

bool Level::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	return true;
}

