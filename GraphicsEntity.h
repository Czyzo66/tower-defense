#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Texture.h"

/*
*	TODO: Reconsider:
*	In SFML sf::Texture::getSize() returns by value, that's why local getSize() is also doing so.
*	Maybe returning by const reference would be a better choice.
*	Same with bounds.
*/

class GraphicsEntity : public sf::Drawable
{
private:
	void init(const std::string& textureFile);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
protected:
	My::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_position;
public:
	GraphicsEntity(const std::string& textureFile);
	GraphicsEntity(const std::string& textureFile, const sf::Vector2f& position);
	GraphicsEntity(const std::string& textureFile, const float x, const float y);

	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPosition(const float x, const float y);

	void setScale(const sf::Vector2f& factors) { m_sprite.setScale(factors); }
	void setScale(const float factorX, const float factorY) { m_sprite.setScale(factorX, factorY); }

	void setOrigin(const sf::Vector2f& origin) { m_sprite.setOrigin(origin); }
	void setOrigin(const float x, const float y) { m_sprite.setOrigin(x, y); }

	const sf::Vector2f& getPosition() const { return m_sprite.getPosition(); }
	sf::Vector2u getSize() const { return m_texture.getSize(); }
	sf::FloatRect getLocalBounds() const { return m_sprite.getLocalBounds(); };
	sf::FloatRect getGlobalBounds() const { return m_sprite.getGlobalBounds(); };
};

