#include "Menu.h"


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_title, states);
	target.draw(m_buttonPlay, states);
	target.draw(m_buttonOptions, states);
	target.draw(m_buttonExit, states);
}

Menu::Menu(const sf::Vector2u& targetRes) :
	m_buttonPlay("resources\\menu\\button_play.png", targetRes.x / 2.0, targetRes.y*(5 / 8.0)),
	m_buttonOptions("resources\\menu\\button_options.png", targetRes.x / 2.0, targetRes.y*(6 / 8.0)),
	m_buttonExit("resources\\menu\\button_exit.png", targetRes.x / 2.0, targetRes.y*(7 / 8.0)),
	m_background("resources\\menu\\background.jpg"),
	m_title("resources\\menu\\title.png", targetRes.x / 2.0, targetRes.y*(2.2 / 8.0))
{
	m_title.setOrigin(m_title.getGlobalBounds().width / 2, m_title.getGlobalBounds().height / 2);
	m_title.setScale(static_cast<double>(targetRes.x) / m_background.getSize().x, static_cast<double>(targetRes.y) / m_background.getSize().y);
}

void Menu::rescaleButtons(const float scale)
{
	m_buttonPlay.rescale(scale);
	m_buttonOptions.rescale(scale);
	m_buttonExit.rescale(scale);
}
