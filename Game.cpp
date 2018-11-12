#include "Game.h"


void Game::releaseEnemy(int enemyIndex, sf::Time time)
{
	if (m_clock.getElapsedTime() > time)
	{
		if (m_enemies[enemyIndex] == nullptr)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndex);
			m_enemies.shrink_to_fit();
			return;
		}
		if (m_enemies[enemyIndex]->getTrack().empty())
		{
			m_enemies[enemyIndex].reset();
			return;
		}
		if (m_enemies[enemyIndex]->isActive() == false)
		{
			m_enemies[enemyIndex]->resetTimer();
			m_enemies[enemyIndex]->setActive(true);
		}
		m_enemies[enemyIndex]->move();
		window.draw(*m_enemies[enemyIndex]);
	}
}

int Game::initializeGame()
{
	std::vector<sf::VideoMode> res(sf::VideoMode::getFullscreenModes());
	window.create(res[0], "Post-Ironic Aesthetic Experience", sf::Style::Fullscreen);
	
	setCursor();
	window.setMouseCursorGrabbed(true);
	int ret = 0;
	ret = m_menu.load(window);
	if (ret) return ret;

	//level
	Level level;
	m_levels.push_back(level);
	ret = m_levels[0].load(window, "levels\\level_1.png", "levels\\level_1_track.png", "levels\\level_1_data.txt");
	if (ret) return ret;
	//_level

	//enemies
	//for testing:
	int numberOfEnemies = 20;
	for (int i = 1; i < numberOfEnemies + 1; ++i)
	{
		m_enemies.push_back(std::unique_ptr<Enemy>(new Enemy(i%5)));
	}
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
							int i = 0;
							for (std::unique_ptr<Enemy>& enemy : m_enemies)
							{
								if(i < 10)
									enemy->setTrack(m_levels[m_currentLevel].getTracks()[0]);
								else
									enemy->setTrack(m_levels[m_currentLevel].getTracks()[1]);
								enemy->resetTimer();
								++i;
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
		for (int i = 0; i < m_enemies.size(); ++i)
		{
			releaseEnemy(i, sf::seconds(i));
		}
		break;
	default:
		break;
	}
	window.display();
}

