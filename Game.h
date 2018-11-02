#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Audio.hpp>
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
	PLAYER_IN_GAME,
};

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock m_clock;
	sf::Image m_iCursor;
	sf::Cursor m_cursor;
	int m_playerState;
	std::vector<bool> m_isButtonActive;
	std::vector<Enemy> m_enemies;
	std::vector<Level> m_levels;
	int m_currentLevel;
	Menu m_menu;
public:
	int initializeGame();
	const sf::RenderWindow& getWindow() const;
	bool setCursor();
	void eventLoop();
	void display();
	Game() : m_currentLevel(0), m_playerState(Player::PLAYER_IN_MENU) {};
};