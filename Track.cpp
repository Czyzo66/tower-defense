#include "Track.h"

int Track::loadFirstPointCoords(const sf::Color color)
{
	sf::Vector2f nextCoords = m_track.back();
	sf::Vector2u fileSize = m_trackTexture.getSize();
	if (m_trackTexture.getPixel(--nextCoords.x, --nextCoords.y) == color && nextCoords.x > 0 && nextCoords.y > 0)
		saveAndPush(nextCoords);
	else if (m_trackTexture.getPixel(++nextCoords.x, nextCoords.y) == color && nextCoords.y > 0)
		save(nextCoords);
	else if (m_trackTexture.getPixel(++nextCoords.x, nextCoords.y) == color && nextCoords.x < fileSize.x && nextCoords.y > 0)
		saveAndPush(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, ++nextCoords.y) == color && nextCoords.x < fileSize.x)
		save(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, ++nextCoords.y) == color && nextCoords.x < fileSize.x && nextCoords.y < fileSize.y)
		saveAndPush(nextCoords);
	else if (m_trackTexture.getPixel(--nextCoords.x, nextCoords.y) == color && nextCoords.y < fileSize.y)
		save(nextCoords);
	else if (m_trackTexture.getPixel(--nextCoords.x, nextCoords.y) == color && nextCoords.x > 0 && nextCoords.y < fileSize.y)
		saveAndPush(nextCoords);
	else if (m_trackTexture.getPixel(nextCoords.x, --nextCoords.y) == color && nextCoords.x > 0)
		save(nextCoords);
	else return Error::ERROR_LOADING_TRACK;
	return 0;
}

void Track::save(sf::Vector2f& point)
{
	m_secondLastFoundCoords = m_lastFoundCoords;
	m_lastFoundCoords = point;
}

void Track::saveAndPush(sf::Vector2f& point)
{
	m_track.push_back(point);
	m_secondLastFoundCoords = m_lastFoundCoords;
	m_lastFoundCoords = point;
}

int Track::loadTrack(const std::string& trackTextureFile, const sf::Color color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
{
	if (!m_trackTexture.loadFromFile(trackTextureFile))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Vector2u fileSize = m_trackTexture.getSize();
	m_track.push_back(endCoords);
	int ret = loadFirstPointCoords(color);
	if (ret) return ret;
	sf::Vector2f nextCoords(m_lastFoundCoords);
	sf::Vector2f *ptrNextCoords = &nextCoords;
	while (m_track.back() != startCoords)
	{
		nextCoords = m_lastFoundCoords;
		if (m_trackTexture.getPixel(--ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			save(nextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			save(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			save(nextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != m_secondLastFoundCoords)
			save(nextCoords);
		else if (++ptrNextCoords->x <= 0 || ptrNextCoords->y <= 0 || ptrNextCoords->x >= fileSize.x - 1 || ptrNextCoords->y >= fileSize.y - 1)
			return 0;
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

sf::Vector2f& Track::back()
{
	return m_track.back();
}

sf::Vector2f& Track::front()
{
	return m_track.front();
}

std::vector<sf::Vector2f>::iterator Track::begin()
{
	return m_track.begin();
}

std::vector<sf::Vector2f>::iterator Track::end()
{
	return m_track.end();
}

std::vector<sf::Vector2f>::iterator Track::erase(std::vector<sf::Vector2f>::iterator itr)
{
	return m_track.erase(itr);
}

void Track::pop_back()
{
	m_track.pop_back();
}
