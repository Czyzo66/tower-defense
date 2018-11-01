#include "Level.h"




void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

int Level::load(const std::string& textureFile, const std::string& trackTextureFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_sprite.setTexture(m_texture);
	m_startCoords = sf::Vector2f(1919.0f, 450.0f);
	m_endCoords = sf::Vector2f(0.0f, 1037.0f);
	int ret = m_track.loadTrack(trackTextureFile, sf::Color(255, 0, 0), m_startCoords, m_endCoords);
	if (ret) return ret;
	m_track.rescale(1600, 900);
	return 0;
}

//int Level::loadTrack(const std::string & trackTextureFile)
//{
//	sf::Image trackFile;
//	if (!trackFile.loadFromFile(trackTextureFile))
//		return Error::ERROR_LOADING_TEXTURE;
//	m_track.push_back(m_startCoords);
//	if(trackFile.getPixel(m_track.back().x - 1, m_track.back().y - 1) == sf::Color(255,0,0) &&
//		m_track.back() != sf::Vector2f)
//	return 0;
//}

//bool Level::setTrack(std::vector<sf::Vector2f>& track)
//{
//	m_track = track; 
//	m_startCoords = m_track[0];
//	return true;
//}

bool Level::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	return true;
}

