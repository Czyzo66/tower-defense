#include "Menu.h"


void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_background, states);
	target.draw(m_title, states);
	target.draw(m_buttonPlay, states);
	target.draw(m_buttonOptions, states);
	target.draw(m_buttonExit, states);
}

int Menu::load(sf::RenderWindow& window)
{
	if (!m_tBackground.loadFromFile("textures\\background.jpg"))
		return Error::ERROR_LOADING_TEXTURE;
	m_background.setTexture(m_tBackground);
	if (!m_tTitle.loadFromFile("textures\\title.png"))
		return Error::ERROR_LOADING_TEXTURE;
	m_title.setTexture(m_tTitle);
	m_title.setPosition(sf::Vector2f(((window.getSize().x - m_title.getGlobalBounds().width) / 2), ((window.getSize().y - m_title.getLocalBounds().height) * 0.14)));
	int errorPlay(m_buttonPlay.load("textures\\button_play.png", window.getSize().x / 2, window.getSize().y*(5 / 8.0)));
	if (errorPlay) return errorPlay;
	int errorOptions(m_buttonOptions.load("textures\\button_options.png", window.getSize().x / 2, window.getSize().y*(6 / 8.0)));
	if (errorOptions) return errorOptions;
	int errorExit(m_buttonExit.load("textures\\button_exit.png", window.getSize().x / 2, window.getSize().y*(7 / 8.0)));
	if (errorExit) return errorExit;
	return 0;
}

void Menu::rescaleButtons(float scale) //call before draw!
{
	m_buttonPlay.rescale(scale);
	m_buttonOptions.rescale(scale);
	m_buttonExit.rescale(scale);
}

const sf::FloatRect& Menu::getPlayBoundingBox() const
{
	return m_buttonPlay.getBoundingBox();
}

const sf::FloatRect & Menu::getOptionsBoundingBox() const
{
	return m_buttonOptions.getBoundingBox();
}

const sf::FloatRect & Menu::getExitBoundingBox() const
{
	return m_buttonExit.getBoundingBox();
}

void Menu::setPlayActive(bool active)
{
	m_buttonPlay.setActive(active);
}

void Menu::setOptionsActive(bool active)
{
	m_buttonOptions.setActive(active);
}

void Menu::setExitActive(bool active)
{
	m_buttonExit.setActive(active);
}
