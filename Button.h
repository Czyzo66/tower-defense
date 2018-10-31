#pragma once
#include <SFML/Graphics.hpp>
#include <string>
//#include <vector>
//#include <cmath>
#include "Error.h"

class Button : public sf::Drawable
{
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::FloatRect m_boundingBox;
	bool m_isActive;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int load(const std::string& textureFile);
	int load(const std::string& textureFile, const sf::Vector2f& position);
	int load(const std::string& textureFile, const float positionX, const float positionY);
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float positionX, const float positionY);
	void setActive(bool active);
	void rescale(float scale);
	const sf::FloatRect& getBoundingBox() const;
};

