#include "Track.h"

void Track::loadFirstPoint(const sf::Color& color)
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
	else return;// Error::ERROR_TRACK_IS_CORRUPTED;
}

void Track::loadRemainingPoints(const sf::Vector2f& startCoords, const sf::Color& color, const sf::Vector2u& textureSize)
{
	sf::Vector2f nextCoords(m_lastFoundPoint);
	sf::Vector2f *ptrNextCoords = &nextCoords;
	while (m_track.back() != startCoords)
	{
		nextCoords = m_lastFoundPoint;
		if (m_trackTexture.getPixel(--ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			save(nextCoords);
		else if (m_trackTexture.getPixel(++ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			save(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, ++ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			save(nextCoords);
		else if (m_trackTexture.getPixel(--ptrNextCoords->x, ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			saveAndPush(nextCoords);
		else if (m_trackTexture.getPixel(ptrNextCoords->x, --ptrNextCoords->y) == color && *ptrNextCoords != m_secondlastFoundPoint)
			save(nextCoords);
		else if (++ptrNextCoords->x <= 0 || ptrNextCoords->y <= 0 || ptrNextCoords->x >= textureSize.x - 1 || ptrNextCoords->y >= textureSize.y - 1)
			m_track.push_back(startCoords);
		else return;// Error::ERROR_TRACK_IS_CORRUPTED;
	}
}

void Track::loadOffscreenPoint(const sf::Vector2f& startOrEndCoords, const sf::Vector2u& textureSize)
{
	if (startOrEndCoords.x == 0)
		m_track.push_back(sf::Vector2f(-100, startOrEndCoords.y));
	else if (startOrEndCoords.y == 0)
		m_track.push_back(sf::Vector2f(startOrEndCoords.x, -100));
	else if (startOrEndCoords.x == textureSize.x - 1)
		m_track.push_back(sf::Vector2f(textureSize.x + 99, startOrEndCoords.y));
	else if (startOrEndCoords.y == textureSize.y - 1)
		m_track.push_back(sf::Vector2f(startOrEndCoords.x, textureSize.y + 99));
}

void Track::save(const sf::Vector2f& point)
{
	m_secondlastFoundPoint = m_lastFoundPoint;
	m_lastFoundPoint = point;
}

void Track::saveAndPush(const sf::Vector2f& point)
{
	m_track.push_back(point);
	m_secondlastFoundPoint = m_lastFoundPoint;
	m_lastFoundPoint = point;
}

void Track::skipChars(std::ifstream & inf) const
{
	char ch = 0;
	while (ch != '[')
		inf >> ch;
}

Track::Track(const std::string & trackTextureFile, const sf::Color & color, const sf::Vector2f & startCoords, const sf::Vector2f & endCoords)
{
	loadTrack(trackTextureFile, color, startCoords, endCoords);
}

Track::Track(std::ifstream & inf, const std::string & trackTextureFile)
{
	loadFromFile(inf, trackTextureFile);
}

void Track::loadTrack(const std::string& trackTextureFile, const sf::Color& color, const sf::Vector2f& startCoords, const sf::Vector2f& endCoords)
{
	if (!m_trackTexture.loadFromFile(trackTextureFile))
	{
		throw Error::ERROR_TRACK_LOADING_TEXTURE;
		return;
	}		
	sf::Vector2u textureSize = m_trackTexture.getSize();
	loadOffscreenPoint(endCoords, textureSize);
	m_track.push_back(endCoords);
	loadFirstPoint(color);
	loadRemainingPoints(startCoords, color, textureSize);
	loadOffscreenPoint(startCoords, textureSize);
	//Error::ERROR_TRACK_IS_CORRUPTED can be thrown
}

void Track::loadFromFile(std::ifstream& inf, const std::string& trackTextureFile)
{
	float startCoordsX, startCoordsY, endCoordsX, endCoordsY;
	int r, g, b;
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
	skipChars(inf);
	loadTrack(trackTextureFile, sf::Color(r, g, b), sf::Vector2f(startCoordsX, startCoordsY), sf::Vector2f(endCoordsX, endCoordsY));
	//Error::ERROR_TRACK_LOADING_TEXTURE can be thrown
}

void Track::rescale(const sf::Vector2f& screenRes)
{
	for (sf::Vector2f& point : m_track)
	{
		point.x *= screenRes.x / m_trackTexture.getSize().x;
		point.y *= screenRes.y / m_trackTexture.getSize().y;
	}
}

void Track::rescale(const sf::Vector2u& screenRes)
{
	for (sf::Vector2f& point : m_track)
	{
		point.x *= static_cast<float>(screenRes.x) / m_trackTexture.getSize().x;
		point.y *= static_cast<float>(screenRes.y) / m_trackTexture.getSize().y;
	}
}

void Track::rescale(const float resX, const float resY)
{
	rescale(sf::Vector2f(resX, resY));
}

void Track::rescale(const sf::RenderTarget& target)
{
	rescale(target.getSize());
}
