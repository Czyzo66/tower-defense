#include "Enemy.h"

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	switch (m_state)
	{
	case Enemy::State::STATE_LEFT:
		target.draw(m_left, states);
		break;
	case Enemy::State::STATE_MID:
		target.draw(m_mid, states);
		break;
	case Enemy::State::STATE_RIGHT:
		target.draw(m_right, states);
		break;
	default:
		target.draw(m_mid, states);
		break;
	}
}

int Enemy::load(const std::string& textureFile, sf::Vector2f enemySize)
{
	m_size = enemySize;
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	sf::Vector2i pos(0, 0);
	sf::Vector2i textsize(112, 112);
	m_left.setTexture(m_texture);
	m_mid.setTexture(m_texture);
	m_right.setTexture(m_texture);
	m_left.setTextureRect(sf::IntRect(pos, textsize));
	pos.x += m_texture.getSize().x / 3;
	m_mid.setTextureRect(sf::IntRect(pos, textsize));
	pos.x += m_texture.getSize().x / 3;
	m_right.setTextureRect(sf::IntRect(pos, textsize));
	m_left.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / m_texture.getSize().y);
	m_mid.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / (m_texture.getSize().y));
	m_right.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / m_texture.getSize().y);
	return 0;
}

//bool Enemy::calculateTrack(std::vector<sf::Vector2f>& track, int targetX, int targetY, int textureX, int textureY)
//{
//	m_track = track;
//	m_track.shrink_to_fit();
//	for (int i = 0; i < m_track.capacity(); ++i)
//	{
//		m_track[i].x *= targetX / textureX;
//		m_track[i].y *= targetY / textureY;
//	}
//	setPosition(m_track[0]);
//	m_track.erase(m_track.begin());
//	return true;
//}
//
//bool Enemy::calculateTrack(std::vector<sf::Vector2f>& track, sf::Vector2u targetSize, sf::Vector2u textureSize)
//{
//	m_track.clear();
//	m_track = track;
//	m_track.shrink_to_fit();
//	for (sf::Vector2f& trackPoint : m_track)
//	{
//		trackPoint.x *= static_cast<double>(targetSize.x) / textureSize.x;
//		trackPoint.y *= static_cast<double>(targetSize.y) / textureSize.y;		
//	}
//	setPosition(m_track[0]);
//	m_track.erase(m_track.begin());
//	return true;
//}

void Enemy::setTrack(Track& track)
{
	m_track = track;
	setPosition(m_track.front());
}

//bool Enemy::setTrack(std::vector<sf::Vector2f>& track)
//{
//	m_track = track;
//	return true;
//}

bool Enemy::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_left.setPosition(m_position);
	m_mid.setPosition(m_position);
	m_right.setPosition(m_position);
	return true;
}

bool Enemy::move()
{
	sf::Time delta = m_clock.restart();
	//int delta = 100000; //debuging
	if (m_track.empty())
		return false;
	double moveDistance = static_cast<double>(delta.asMicroseconds()) * m_speed / 50000; //todo: magic number??
	sf::Vector2f destination(m_track.front());
	float angle;
	if (destination.y != m_position.y && destination.x != m_position.x)
		angle = atan((fabs(destination.x - m_position.x) / fabs(destination.y - m_position.y)));
	else
		angle = 90.0;
	sf::Vector2f movementVector;
	if (destination.x >= m_position.x && destination.y > m_position.y)
	{
		movementVector.x = sin(angle) * moveDistance;
		movementVector.y = cos(angle) * moveDistance;
	}
	else if (destination.x <= m_position.x && destination.y < m_position.y)
	{
		movementVector.x = -sin(angle) * moveDistance;
		movementVector.y = -cos(angle) * moveDistance;
	}
	else if (destination.x > m_position.x && destination.y <= m_position.y)
	{
		movementVector.x = sin(angle) * moveDistance;
		movementVector.y = -cos(angle) * moveDistance;
	}
	else if (destination.x < m_position.x && destination.y >= m_position.y)
	{
		movementVector.x = -sin(angle) * moveDistance;
		movementVector.y = cos(angle) * moveDistance;
	}

	if (fabs(movementVector.x) <= fabs(movementVector.y))
		m_state = Enemy::State::STATE_MID;
	else
	{
		if (movementVector.x < 0)
			m_state = Enemy::State::STATE_LEFT;
		else
			m_state = Enemy::State::STATE_RIGHT;
	}

	if (fabs(destination.x - m_position.x) <= fabs(movementVector.x) && fabs(destination.y - m_position.y) <= fabs(movementVector.y))
	{
		setPosition(destination);
		m_track.erase(m_track.begin());
	}
	else
	{
		setPosition(m_position + movementVector);
	}
	return true;
}

void Enemy::resetTimer()
{
	m_clock.restart();
}