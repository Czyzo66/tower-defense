#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Texture.h"
#include "GraphicsEntity.h"
#include "Error.h"

/*
 *	TODO: Buttons scaling dependent on window resolution
 */

class Menu : public sf::Drawable
{
private:
	Button m_buttonPlay;
	Button m_buttonOptions;
	Button m_buttonExit;
	GraphicsEntity m_background;
	GraphicsEntity m_title;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;	
public:
	Menu(const sf::Vector2u& targetRes);
	void rescaleButtons(const float scale = 1.1);
	const sf::FloatRect& getPlayBoundingBox() const { return m_buttonPlay.getBoundingBox(); }
	const sf::FloatRect& getOptionsBoundingBox() const { return m_buttonOptions.getBoundingBox(); }
	const sf::FloatRect& getExitBoundingBox() const { return m_buttonExit.getBoundingBox(); }
	void setPlayActive(bool active) { m_buttonPlay.setActive(active); }
	void setOptionsActive(bool active) { m_buttonOptions.setActive(active); }
	void setExitActive(bool active) { m_buttonExit.setActive(active); }
};

