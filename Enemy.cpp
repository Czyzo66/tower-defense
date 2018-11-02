#include "Enemy.h"

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

int Enemy::load(const std::string& textureFile, sf::Vector2f enemySize)
{
	m_size = enemySize;
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(112, 112)));
	m_sprite.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / m_texture.getSize().y);
	m_sprite.setOrigin(m_texture.getSize().x / 6.0, m_texture.getSize().y / 2);
	return 0;
}

void Enemy::setTrack(Track& track)
{
	m_track = track;
	setPosition(m_track.back());
}

void Enemy::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

//void Enemy::move_test()
//{
//	//laggy!
//	sf::Time delta = m_clock.restart();
//	//int delta = 100000; //debuging
//	if (m_track.empty())
//		return;
//	double targetDistance = static_cast<double>(delta.asMicroseconds()) * m_speed;
//	sf::Vector2f destination(m_track.back());
//	double moveDistance(0); //sqrt(pow(destination.x, 2) + pow(destination.y, 2))
//	while (moveDistance < targetDistance)
//	{
//		moveDistance += sqrt(pow(destination.x - m_position.x, 2) + pow(destination.y - m_position.y, 2));
//		setPosition(destination);
//		//if (m_track.erase(m_track.begin()) == m_track.end()) return;
//		m_track.pop_back();
//		if (m_track.empty()) return;
//		destination = m_track.back();
//	}
//}

bool Enemy::move()
{
	sf::Time delta = m_clock.restart();
	//int delta = 100000; //debuging
	if (m_track.empty())
		return false;
	double moveDistance = static_cast<double>(delta.asMicroseconds()) * m_speed / 50000; //todo: magic number??
	sf::Vector2f destination(m_track.back());
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

	if (fabs(movementVector.x) <= fabs(movementVector.y) && m_state != Enemy::State::STATE_MID)
	{
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(112, 0), sf::Vector2i(112, 112)));
		m_state = Enemy::State::STATE_MID;
	}
	else if(movementVector.x < 0 && m_state != Enemy::State::STATE_LEFT)
	{
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(112, 112)));
		m_state = Enemy::State::STATE_LEFT;
	}
	else if (movementVector.x > 0 && m_state != Enemy::State::STATE_RIGHT)
	{
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(224, 0), sf::Vector2i(112, 112)));
		m_state = Enemy::State::STATE_RIGHT;
	}

	if (fabs(destination.x - m_position.x) <= fabs(movementVector.x) && fabs(destination.y - m_position.y) <= fabs(movementVector.y))
	{
		setPosition(destination);
		m_track.pop_back();
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