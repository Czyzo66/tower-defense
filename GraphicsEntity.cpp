#include "GraphicsEntity.h"


void GraphicsEntity::init(const std::string& textureFile)
{
	m_texture.loadFromFile(textureFile);
	m_texture.setSmooth(true);
	m_sprite.setTexture(m_texture);
}

void GraphicsEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_sprite, states);
}

GraphicsEntity::GraphicsEntity(const std::string& textureFile)
{
	init(textureFile);
}

GraphicsEntity::GraphicsEntity(const std::string& textureFile, const sf::Vector2f& position)
{
	init(textureFile);
	setPosition(position);
}

GraphicsEntity::GraphicsEntity(const std::string& textureFile, const float x, const float y)
	: GraphicsEntity(textureFile, sf::Vector2f(x, y))
{
}

GraphicsEntity::GraphicsEntity(const GraphicsEntity & graphicsEntity)
{
	m_texture = graphicsEntity.m_texture;
	m_sprite = graphicsEntity.m_sprite;
	m_position = graphicsEntity.m_position;
	m_sprite.setTexture(m_texture);
}

void GraphicsEntity::setPosition(const sf::Vector2f & position)
{
	m_position = position;
	m_sprite.setPosition(position);
}

void GraphicsEntity::setPosition(const float x, const float y)
{
	m_position = sf::Vector2f(x, y);
	m_sprite.setPosition(x, y);
}
