#include "Enemy.h"

std::map<int, EnemyProperties> initProps(const std::string& propsFile)
{
	std::map<int, EnemyProperties> temp;
	std::ifstream inf(propsFile);
	assert(inf);
	if (!inf) exit(Error::ERROR_LOADING_TEXT_FILE);
	std::string tname, tfile;
	double thp, tspeed;
	sf::Vector2f tsize;
	float tvecx, tvecy;
	int ctr = 0;
	while (inf >> tname && inf >> thp && inf >> tspeed && inf >> tvecx && inf >> tvecy && inf >> tfile)
	{		
		temp.insert(std::move(std::pair<int, EnemyProperties>(ctr, EnemyProperties(tname, thp, tspeed, sf::Vector2f(tvecx, tvecy), tfile))));
		++ctr;
	}
	return temp;
}

std::map<int, EnemyProperties> Enemy::s_enemyProperties(initProps("resources\\enemies\\enemy_properties.txt"));

Enemy::Enemy(const int id, const Track* trackPtr) :
	GraphicsEntity(s_enemyProperties[id].getTextureFile()),
	m_id(id),
	m_trackPtr(trackPtr),
	m_hp(s_enemyProperties[id].getHp()),
	m_speed(s_enemyProperties[id].getSpeed()),
	m_size(s_enemyProperties[id].getSize()),
	m_trackCounter(trackPtr->size() - 1),
	m_state(0),
	m_active(false)
{
	init();
}

void Enemy::init()
{
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().y)));
	m_sprite.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / m_texture.getSize().y);
	m_sprite.setOrigin(m_texture.getSize().x / 6.0, m_texture.getSize().y);
	setPosition(m_trackPtr->back());
}

void Enemy::setTrack(const Track* track)
{
	m_trackPtr = track;
	assert(m_trackPtr != nullptr);
	if (m_trackPtr == nullptr)
	{
		m_state = Enemy::State::STATE_ERROR_LOADING_TRACK;
		return;
	}
	setPosition(m_trackPtr->back());
}

void Enemy::move()
{
	//int delta = 100000; //debuging
	if (m_state == Enemy::State::STATE_REACHED_END)
		return;
	assert(m_trackPtr != nullptr);
	if (m_trackPtr == nullptr || m_trackCounter < 0)
	{
		m_state = Enemy::State::STATE_ERROR_LOADING_TRACK;
		return;
	}	
	sf::Vector2f destination;
	try
	{
		destination = m_trackPtr->at(m_trackCounter);
	}
	catch (const std::out_of_range)
	{
		m_state = Enemy::State::STATE_REACHED_END;
		return;
	}
	float angle;
	if (destination.y != m_position.y && destination.x != m_position.x)
		angle = atan((fabs(destination.x - m_position.x) / fabs(destination.y - m_position.y)));
	else
		angle = 90.0;
	sf::Time delta = m_clock.restart();
	double moveDistance = static_cast<double>(delta.asMicroseconds()) * m_speed;
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

	//1.2 and 0.8 factors are used to remove floating point inaccuracy influence when movement angle is close to 45 degrees
	if(1.2*fabs(movementVector.x) < fabs(movementVector.y) && m_state != Enemy::State::STATE_MID)
	{
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_texture.getSize().x / 3.0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().y)));
		m_state = Enemy::State::STATE_MID;
	}
	else if(0.8*fabs(movementVector.x) > fabs(movementVector.y))
	{
		if (movementVector.x < 0 && m_state != Enemy::State::STATE_LEFT)
		{

			m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().y)));
			m_state = Enemy::State::STATE_LEFT;
		}
		else if (movementVector.x > 0 && m_state != Enemy::State::STATE_RIGHT)
		{
			m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_texture.getSize().x * 2 / 3.0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().y)));
			m_state = Enemy::State::STATE_RIGHT;
		}
	}

	if (fabs(destination.x - m_position.x) <= fabs(movementVector.x) && fabs(destination.y - m_position.y) <= fabs(movementVector.y))
	{
		setPosition(destination);
		--m_trackCounter;
	}
	else
	{
		setPosition(m_position + movementVector);
	}
}

void Enemy::resetTimer()
{
	m_clock.restart();
}

