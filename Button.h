#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Error.h"
#include "GraphicsEntity.h"

class Button : public GraphicsEntity
{
private:
	sf::FloatRect m_boundingBox;
	bool m_isActive;
	void init();
public:
	Button(const std::string& textureFile) : GraphicsEntity(textureFile) { init(); }
	Button(const std::string& textureFile, const sf::Vector2f& position) : GraphicsEntity(textureFile, position) { init(); }
	Button(const std::string& textureFile, const float positionX, const float positionY) : GraphicsEntity(textureFile, positionX, positionY) { init(); }
	const sf::FloatRect& getBoundingBox() const { return m_boundingBox; }
	virtual void setPosition(const sf::Vector2f& position);
	virtual void setPosition(const float positionX, const float positionY);
	void setActive(bool active);
	void rescale(const float scale);
};