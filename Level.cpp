#include "Level.h"


void Level::skipChars(std::ifstream& inf) const
{
	char ch = 0;
	while (ch != '[')
		inf >> ch;
}

int Level::load(const sf::RenderWindow& window, const std::string& textureFile, const std::string& trackTextureFile, const std::string& trackDataFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LEVEL_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(static_cast<float>(window.getSize().x) / m_texture.getSize().x, static_cast<float>(window.getSize().y) / m_texture.getSize().y);
	std::ifstream inf(trackDataFile);
	if (!inf)
		return Error::ERROR_LEVEL_LOADING_FILE;
	skipChars(inf);
	while (inf.peek() != 'e')
	{
		m_tracks.push_back(Track(inf, trackTextureFile));
		m_tracks.back().rescale(window.getSize());
	}
	skipChars(inf);
	while (inf.peek() != 'e')
	{
		/*Wave twave;
		int ret = twave.loadFromFile(inf, &m_tracks);
		if (ret) return ret;
		m_waves.push_back(twave);*/
 		m_waves.push_back(Wave(inf, &m_tracks)); // enemies sprite texture lost here!!!
	}
	return 0;
}
