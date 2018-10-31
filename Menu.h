#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Error.h"

class Menu : public sf::Drawable
{
private:
	Button m_buttonPlay;
	Button m_buttonOptions;
	Button m_buttonExit;
	sf::Texture m_tBackground;
	sf::Sprite m_background;
	sf::Texture m_tTitle;
	sf::Sprite m_title;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
public:
	int load(sf::RenderWindow& window);
	void rescaleButtons(float scale = 1.1); //call before draw!
	const sf::FloatRect& getPlayBoundingBox() const;
	const sf::FloatRect& getOptionsBoundingBox() const;
	const sf::FloatRect& getExitBoundingBox() const;
	void setPlayActive(bool active);
	void setOptionsActive(bool active);
	void setExitActive(bool active);
};

