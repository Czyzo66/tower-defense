#include "Button.h"


void Button::init()
{
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	m_boundingBox = m_sprite.getGlobalBounds();
	m_isActive = false;
}

void Button::setPosition(const sf::Vector2f& position)
{
	GraphicsEntity::setPosition(position);
	m_boundingBox = m_sprite.getGlobalBounds();
}

void Button::setPosition(const float positionX, const float positionY)
{
	GraphicsEntity::setPosition(positionX, positionY);
	m_boundingBox = m_sprite.getGlobalBounds();
}

void Button::setActive(bool active)
{
	m_isActive = active;
}

void Button::rescale(const float scale)
{
	if (m_isActive && m_sprite.getScale().x < scale && m_sprite.getScale().y < scale)
		m_sprite.setScale(scale, scale);
	else if (!m_isActive)
		m_sprite.setScale(1, 1);
}
