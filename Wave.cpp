#include "Wave.h"

void Wave::skipChars(std::ifstream & inf) const
{
	char ch = 0;
	while (ch != '[')
		inf >> ch;
}

void Wave::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (const Enemy& enemy : m_enemies)
	{
		if (enemy.isActive())
			target.draw(enemy, states);
	}
}

int Wave::loadFromFile(std::ifstream & inf, std::vector<Track>* ptrTracks)
{
	int trackNum, timeAsMilliseconds;
	sf::Time time;
	inf >> trackNum;
	skipChars(inf);
	inf >> timeAsMilliseconds;
	m_startTime = sf::milliseconds(timeAsMilliseconds);
	skipChars(inf);
	while (inf.peek() != 'e')
	{
		int qty, id;
		inf >> id;
		skipChars(inf);
		inf >> qty;
		skipChars(inf);
		for (int i = 0; i < qty; ++i)
		{
			m_enemies.push_back(Enemy(id, &ptrTracks->at(trackNum)));
		}		
	}
	skipChars(inf);
	return 0;
}

void Wave::release(sf::Clock& clock)
{
	if (!m_active && clock.getElapsedTime().asMilliseconds() == m_startTime.asMilliseconds())
	{
		m_active = true;
		for (Enemy& enemy : m_enemies)
		{
			enemy.setActive(true);
			enemy.resetTimer();
		}
	}
	else if (m_active)
	{
		for (Enemy& enemy : m_enemies)
		{
			enemy.move();
		}
	}
	
}
