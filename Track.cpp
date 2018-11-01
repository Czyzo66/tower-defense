#include "Track.h"

int Track::loadFirstPointCoords(const sf::Color color)
{
	sf::Vector2f nextCoords = m_track.front();
	sf::Vector2u fileSize = m_trackTexture.getSize();
	if (m_trackTexture.getPixel(--nextCoords.x, --nextCoords.y) == color && nextCoords.x > 0 && nextCoords.y > 0)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(++nextCoords.x, nextCoords.y) == color && nextCoords.y > 0)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(++nextCoords.x, nextCoords.y) == color && nextCoords.x < fileSize.x && nextCoords.y > 0)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, ++nextCoords.y) == color && nextCoords.x < fileSize.x)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, ++nextCoords.y) == color && nextCoords.x < fileSize.x && nextCoords.y < fileSize.y)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(--nextCoords.x, nextCoords.y) == color && nextCoords.y < fileSize.y)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(--nextCoords.x, nextCoords.y) == color && nextCoords.x > 0 && nextCoords.y < fileSize.y)
		m_track.push_back(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, --nextCoords.y) == color && nextCoords.x > 0)
		m_track.push_back(nextCoords);
	else return Error::ERROR_LOADING_TRACK;
	return 0;
}

int Track::loadTrack(const std::string& trackTextureFile, const sf::Color color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
{
	if (!m_trackTexture.loadFromFile(trackTextureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_track.push_back(startCoords);
	int ret = loadFirstPointCoords(color);
	if (ret) return ret;
	while (m_track.back() != endCoords)
	{
		sf::Vector2f pprevCoords = m_track[m_track.size() - 2];
		sf::Vector2f prevCoords = m_track[m_track.size() - 1];
		sf::Vector2f nextCoords = prevCoords;
		sf::Vector2f *ptrNextCoords = &nextCoords;
		if (m_trackTexture.getPixel(--ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != pprevCoords)
			m_track.push_back(*ptrNextCoords);
		else return Error::ERROR_LOADING_TRACK;
	}
	return 0;
}

bool Track::empty() const
{
	return m_track.empty();
}

void Track::rescale(sf::Vector2f screenRes)
{
	for (sf::Vector2f& point : m_track)
	{
		point.x *= screenRes.x / m_trackTexture.getSize().x;
		point.y *= screenRes.y / m_trackTexture.getSize().y;
	}
}

void Track::rescale(sf::Vector2u screenRes)
{
	for (sf::Vector2f& point : m_track)
	{
		point.x *= static_cast<float>(screenRes.x) / m_trackTexture.getSize().x;
		point.y *= static_cast<float>(screenRes.y) / m_trackTexture.getSize().y;
	}
}

void Track::rescale(float resX, float resY)
{
	rescale(sf::Vector2f(resX, resY));
}

void Track::rescale(sf::RenderTarget& target)
{
	rescale(target.getSize());
}

sf::Vector2f Track::back() const
{
	return m_track.back();
}

sf::Vector2f Track::front() const
{
	return m_track.front();
}

std::vector<sf::Vector2f>::iterator Track::begin()
{
	return m_track.begin();
}

std::vector<sf::Vector2f>::iterator Track::erase(std::vector<sf::Vector2f>::iterator itr)
{
	return m_track.erase(itr);
}
