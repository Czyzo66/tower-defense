#include "Enemy.h"

std::map<int, EnemyProperties> init(const std::string& propsFile)
{
	std::map<int, EnemyProperties> temp;
	std::ifstream inf(propsFile);
	assert(inf);
	int ctr = 0;
	std::string tname, tfile;
	double thp, tspeed;
	sf::Vector2f tsize;
	float tvecx, tvecy;
	while (inf >> tname && inf >> thp && inf >> tspeed && inf >> tvecx && inf >> tvecy && inf >> tfile)
	{		
		temp.insert(std::pair<int, EnemyProperties>(ctr, EnemyProperties(tname, thp, tspeed, sf::Vector2f(tvecx, tvecy), tfile)));
		++ctr;
	}
	return temp;
}

std::map<int, EnemyProperties> Enemy::s_enemyProperties(init("enemy_properties.txt"));

void Enemy::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

Enemy::Enemy(const int id) :
	m_hp(s_enemyProperties[id].getHp()),
	m_speed(s_enemyProperties[id].getSpeed()),
	m_size(s_enemyProperties[id].getSize()),
	m_position(sf::Vector2f(0, 0)),
	m_state(0),
	m_active(false)
{
	load(s_enemyProperties[id].getTextureFile());
}

int Enemy::load(const std::string& textureFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().x / 3.0)));
	m_sprite.setScale(m_size.x / (m_texture.getSize().x / 3.0), m_size.y / m_texture.getSize().y);
	m_sprite.setOrigin(m_texture.getSize().x / 6.0, m_texture.getSize().y);
	return 0;
}

void Enemy::setTrack(Track track)
{
	m_track = track;
	setPosition(m_track.back());
}

void Enemy::setPosition(sf::Vector2f position)
{
	m_position = position;
	m_sprite.setPosition(m_position);
}

bool Enemy::move()
{
	sf::Time delta = m_clock.restart();
	//int delta = 100000; //debuging
	if (m_track.empty())
		return false;
	double moveDistance = static_cast<double>(delta.asMicroseconds()) * m_speed;
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

	//1.2 and 0.8 factors are used to remove floating point inaccuracy influence when movement angle is close to 45 degrees
	if(1.2*fabs(movementVector.x) < fabs(movementVector.y) && m_state != Enemy::State::STATE_MID)
	{
		m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_texture.getSize().x / 3.0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().x / 3.0)));
		m_state = Enemy::State::STATE_MID;
	}
	else if(0.8*fabs(movementVector.x) > fabs(movementVector.y))
	{
		if (movementVector.x < 0 && m_state != Enemy::State::STATE_LEFT)
		{

			m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().x / 3.0)));
			m_state = Enemy::State::STATE_LEFT;
		}
		else if (movementVector.x > 0 && m_state != Enemy::State::STATE_RIGHT)
		{
			m_sprite.setTextureRect(sf::IntRect(sf::Vector2i(m_texture.getSize().x * 2 / 3.0, 0), sf::Vector2i(m_texture.getSize().x / 3.0, m_texture.getSize().x / 3.0)));
			m_state = Enemy::State::STATE_RIGHT;
		}
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

