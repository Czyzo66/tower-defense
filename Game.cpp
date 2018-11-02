#include "Game.h"


void Game::releaseEnemy(int enemyIndex, sf::Time time)
{
	if (m_clock.getElapsedTime() > time)
	{
		if (m_enemies[enemyIndex].isActive() == false)
		{
			m_enemies[enemyIndex].resetTimer();
			m_enemies[enemyIndex].setActive(true);
		}
		m_enemies[enemyIndex].move();
		window.draw(m_enemies[enemyIndex]);
	}
}

int Game::initializeGame()
{
	window.create(sf::VideoMode(1600, 900), "Post-Ironic Aesthetic Experience", sf::Style::Fullscreen);
	setCursor();
	window.setMouseCursorGrabbed(true);
	if (m_menu.load(window))
		return ERROR_LOADING_MENU;

	//level
	Level level;
	m_levels.push_back(level);
	m_levels[0].load("levels\\level_1.png", "levels\\level_1_track.png");
	//_level

	//enemies
	m_enemies.push_back(Enemy(420, 3));
	m_enemies.push_back(Enemy(420, 8));
	m_enemies.push_back(Enemy(420, 7));
	m_enemies.push_back(Enemy(420, 6));
	m_enemies.push_back(Enemy(420, 5));
	m_enemies.push_back(Enemy(420, 4));
	m_enemies.push_back(Enemy(420, 2));
	m_enemies.push_back(Enemy(420, 1));
	m_enemies.push_back(Enemy(420, 9));
	m_enemies.push_back(Enemy(420, 10));
	m_enemies[0].load("textures\\hotdog.png", sf::Vector2f(40, 40));//todo: return error if not
	m_enemies[1].load("textures\\hotdog2.png", sf::Vector2f(40, 40));//todo: err
	m_enemies[2].load("textures\\hotdog.png", sf::Vector2f(40, 40));
	m_enemies[3].load("textures\\hotdog2.png", sf::Vector2f(40, 40));
	m_enemies[4].load("textures\\hotdog.png", sf::Vector2f(40, 40));
	m_enemies[5].load("textures\\hotdog2.png", sf::Vector2f(40, 40));
	m_enemies[6].load("textures\\hotdog2.png", sf::Vector2f(40, 40));
	m_enemies[7].load("textures\\hotdog.png", sf::Vector2f(40, 40));
	m_enemies[8].load("textures\\hotdog.png", sf::Vector2f(40, 40));
	m_enemies[9].load("textures\\hotdog2.png", sf::Vector2f(40, 40));
	//_enemies	
	return 0;
}

const sf::RenderWindow& Game::getWindow() const
{
	return window;
}

bool Game::setCursor()
{
	m_iCursor.loadFromFile("textures\\cursor.png");
	m_cursor.loadFromPixels(m_iCursor.getPixelsPtr(), m_iCursor.getSize(), { 0,0 });
	window.setMouseCursor(m_cursor);
	return true;
}

void Game::eventLoop()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				window.setMouseCursorGrabbed(true);
				break;
			case sf::Event::LostFocus:
				window.setMouseCursorGrabbed(false);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape) m_playerState = Player::PLAYER_IN_MENU;
				break;
			case sf::Event::MouseMoved:
				if (m_menu.getPlayBoundingBox().contains(event.mouseMove.x, event.mouseMove.y))
					m_menu.setPlayActive(true);
				else
					m_menu.setPlayActive(false);
				if (m_menu.getOptionsBoundingBox().contains(event.mouseMove.x, event.mouseMove.y))
					m_menu.setOptionsActive(true);
				else
					m_menu.setOptionsActive(false);
				if (m_menu.getExitBoundingBox().contains(event.mouseMove.x, event.mouseMove.y))
					m_menu.setExitActive(true);
				else
					m_menu.setExitActive(false);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (m_playerState == Player::PLAYER_IN_MENU)
					{
						sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
						if (m_menu.getPlayBoundingBox().contains(static_cast<sf::Vector2f>(mousePosition)))
						{
							m_playerState = Player::PLAYER_IN_GAME;
							for (Enemy& enemy : m_enemies)
							{							
								enemy.setTrack(m_levels[m_currentLevel].getTrack());
								enemy.resetTimer();
							}
							m_clock.restart();
						}
						else if (m_menu.getExitBoundingBox().contains(static_cast<sf::Vector2f>(mousePosition)))
							window.close();
					}
				}
				break;
			default:
				break;
			}
		}
		display();
	}	
}

void Game::display()
{
	window.clear();
	switch (m_playerState)
	{
	case Player::PLAYER_IN_MENU:
		m_menu.rescaleButtons(1.1);
		window.draw(m_menu);
		break;
	case Player::PLAYER_IN_GAME:
		m_levels[m_currentLevel].setScale(sf::Vector2f((static_cast<double>(window.getSize().x) / m_levels[m_currentLevel].getSize().x),
			(static_cast<double>(window.getSize().y) / m_levels[m_currentLevel].getSize().y)));
		window.draw(m_levels[m_currentLevel]);
		releaseEnemy(0, sf::seconds(5));
		releaseEnemy(1, sf::seconds(10));
		releaseEnemy(2, sf::seconds(9));
		releaseEnemy(3, sf::seconds(8));
		releaseEnemy(4, sf::seconds(7));
		releaseEnemy(5, sf::seconds(6));
		releaseEnemy(6, sf::seconds(4));
		releaseEnemy(7, sf::seconds(3));
		releaseEnemy(8, sf::seconds(11));
		releaseEnemy(9, sf::seconds(12));
		break;
	default:
		break;
	}
	window.display();
}

