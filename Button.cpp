#include "Button.h"



void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

int Button::load(const std::string& textureFile)
{
	if (!m_texture.loadFromFile(textureFile))
		return Error::ERROR_LOADING_TEXTURE;
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);	
	m_isActive = false;
	return 0;
}

int Button::load(const std::string& textureFile, const sf::Vector2f& position)
{
	int err(load(textureFile));
	setPosition(position);
	return err;
}

int Button::load(const std::string& textureFile, const float positionX, const float positionY)
{
	int err(load(textureFile));
	setPosition(positionX, positionY);
	return err;
}

void Button::setPosition(const sf::Vector2f& position)
{
	m_sprite.setPosition(position);
	m_boundingBox = m_sprite.getGlobalBounds();
}

void Button::setPosition(const float positionX, const float positionY)
{
	m_sprite.setPosition(positionX, positionY);
	m_boundingBox = m_sprite.getGlobalBounds();
}

void Button::setActive(bool active)
{
	m_isActive = active;
}

void Button::rescale(float scale)
{
	if (m_isActive && m_sprite.getScale().x < scale && m_sprite.getScale().y < scale)
		m_sprite.setScale(scale, scale);
	else if (!m_isActive)
		m_sprite.setScale(1, 1);
}

const sf::FloatRect & Button::getBoundingBox() const
{
	return m_boundingBox;
}
