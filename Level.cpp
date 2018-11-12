#include "Level.h"


void Level::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

void Level::skipChars(std::ifstream& inf)
{
	char ch = 'a';
	while (ch != '[')
		inf >> ch;
}

int Level::load(sf::RenderWindow& window, const std::string& textureFile, const std::string& trackTextureFile, const std::string& trackDataFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(window.getSize().x / m_texture.getSize().x, window.getSize().y / m_texture.getSize().y);
	std::ifstream inf(trackDataFile);
	assert(inf);
	char ch = 'a';
	float startCoordsX, startCoordsY, endCoordsX, endCoordsY;
	int r, g, b = 0;
	while (inf.get() != ';')
	{
		Track tr;
		skipChars(inf);
		inf >> startCoordsX;
		skipChars(inf);
		inf >> startCoordsY;
		skipChars(inf);
		inf >> endCoordsX;
		skipChars(inf);
		inf >> endCoordsY;
		skipChars(inf);
		inf >> r;
		skipChars(inf);
		inf >> g;
		skipChars(inf);
		inf >> b;
		inf >> ch;
		int ret = tr.loadTrack(trackTextureFile, sf::Color(r, g, b), sf::Vector2f(startCoordsX, startCoordsY), sf::Vector2f(endCoordsX, endCoordsY));
		if (ret) return ret;
		m_tracks.push_back(tr);		
		m_tracks.back().rescale(window.getSize());
	}	
	return 0;
}

bool Level::setScale(sf::Vector2f scale)
{
	m_sprite.setScale(scale);
	return true;
}

