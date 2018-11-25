#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <string>
#include <vector>
#include <cmath>
#include "Enemy.h"
#include "Level.h"
#include "Error.h"
#include "Menu.h"

/*
 *	TODO: Better error handling
 */

enum Player
{
	PLAYER_IN_MENU,
	PLAYER_IN_MENU_OPTIONS,
	PLAYER_IN_MENU_LEVEL_SELECTION,
	PLAYER_IN_GAME,
};

class Game
{
private:
	sf::RenderWindow m_window;
	sf::Clock m_clock;
	sf::Image m_iCursor;
	sf::Cursor m_cursor;
	int m_playerState;
	std::vector<bool> m_isButtonActive;
	std::vector<std::unique_ptr<Enemy>> m_enemies;
	std::vector<Level> m_levels;
	int m_currentLevel;
	Menu m_menu;
public:
	Game() : m_window(std::vector<sf::VideoMode>(sf::VideoMode::getFullscreenModes())[0], "Post-Ironic Aesthetic Experience", sf::Style::Fullscreen),
		m_menu(m_window.getSize()), m_currentLevel(0), m_playerState(Player::PLAYER_IN_MENU) 
	{
		setCursor();
		m_window.setMouseCursorGrabbed(true);
	};
	const sf::RenderWindow& getWindow() const { return m_window; }
	int setCursor();
	void eventLoop();
	void display();	
};