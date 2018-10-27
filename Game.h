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

enum Player
{
	PLAYER_IN_MENU,
	PLAYER_IN_GAME,
};

enum Button
{
	BUTTON_PLAY,
	BUTTON_OPTIONS,
	BUTTON_EXIT,
};

class Game
{
private:
	sf::RenderWindow window;
	sf::Clock m_clock;
	sf::Image m_iCursor;
	sf::Cursor m_cursor;
	int m_playerState;
	std::vector<sf::Sprite> m_buttons;
	std::vector<sf::Texture> m_tButtons;
	std::vector<sf::FloatRect> m_rButtons;
	std::vector<bool> m_isButtonActive;
	std::vector<Enemy> m_enemies;
	std::vector<Level> m_levels;
	int m_currentLevel;
	sf::Texture m_tBackground;
	sf::Sprite m_background;
	sf::Texture m_tTitle;
	sf::Sprite m_title;
public:
	int initializeGame();
	const sf::RenderWindow& getWindow() const;
	bool setCursor();
	void eventLoop();
	void display();
	void drawButtons(int btn, float scale);
	Game() : m_currentLevel(0), m_playerState(Player::PLAYER_IN_MENU) {};
};