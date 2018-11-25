#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
class EnemyProperties
{
private:
	std::string m_name;
	double m_hp;
	double m_speed;
	sf::Vector2f m_size;
	std::string m_textureFile;
public:
	EnemyProperties() {};
	EnemyProperties(const std::string& name, const double hp, const double speed, const sf::Vector2f& size, const std::string& textureFile) :
		m_name(name), m_hp(hp), m_speed(speed), m_size(size), m_textureFile(textureFile) {};
	const std::string& getName() const { return m_name; };
	double getHp() const { return m_hp; };
	double getSpeed() const { return m_speed; };
	const sf::Vector2f& getSize() const { return m_size; };
	const std::string& getTextureFile() const { return m_textureFile; };
};

