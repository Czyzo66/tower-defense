#include "Game.h"


//void Game::releaseEnemy(int enemyIndex, sf::Time time)
//{
//	if (m_clock.getElapsedTime() > time)
//	{
//		if (m_enemies[enemyIndex] == nullptr)
//		{
//			m_enemies.erase(m_enemies.begin() + enemyIndex);
//			m_enemies.shrink_to_fit();
//			return;
//		}
//		if (m_enemies[enemyIndex]->getTrack().empty())
//		{
//			m_enemies[enemyIndex].reset();
//			return;
//		}
//		if (m_enemies[enemyIndex]->isActive() == false)
//		{
//			m_enemies[enemyIndex]->resetTimer();
//			m_enemies[enemyIndex]->setActive(true);
//		}
//		m_enemies[enemyIndex]->move();
//		m_window.draw(*m_enemies[enemyIndex]);
//	}
//}

int Game::setCursor()
{
	if (!m_iCursor.loadFromFile("resources\\cursor.png"))
		return Error::ERROR_GAME_LOADING_CURSOR;
	m_cursor.loadFromPixels(m_iCursor.getPixelsPtr(), m_iCursor.getSize(), { 0,0 });
	m_window.setMouseCursor(m_cursor);
	return 0;
}

void Game::eventLoop()
{
	while (m_window.isOpen())
	{
		sf::Event event;
		while (m_window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				m_window.close();
				break;
			case sf::Event::GainedFocus:
				m_window.setMouseCursorGrabbed(true);
				break;
			case sf::Event::LostFocus:
				m_window.setMouseCursorGrabbed(false);
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape)
				{
					m_playerState = Player::PLAYER_IN_MENU;
					m_levels.clear();
				}
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
						sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
						if (m_menu.getPlayBoundingBox().contains(static_cast<sf::Vector2f>(mousePosition)))
						{
							m_playerState = Player::PLAYER_IN_GAME;
							Level level;
							m_levels.push_back(level);
							m_levels[0].load(m_window, "resources\\levels\\level_1.png", "resources\\levels\\level_1_track.png", "resources\\levels\\level_1_data.txt");
							m_levels[m_currentLevel].setScale(sf::Vector2f((static_cast<double>(m_window.getSize().x) / m_levels[m_currentLevel].getSize().x),
								(static_cast<double>(m_window.getSize().y) / m_levels[m_currentLevel].getSize().y)));
							/*int i = 0;
							for (std::unique_ptr<Enemy>& enemy : m_enemies)
							{
								if(i < 10)
									enemy->setTrack(m_levels[m_currentLevel].getTracks()[0]);
								else
									enemy->setTrack(m_levels[m_currentLevel].getTracks()[1]);
								enemy->resetTimer();
								++i;
							}*/
							m_clock.restart();
						}
						else if (m_menu.getExitBoundingBox().contains(static_cast<sf::Vector2f>(mousePosition)))
							m_window.close();
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
	m_window.clear();
	switch (m_playerState)
	{
	case Player::PLAYER_IN_MENU:
		m_menu.rescaleButtons(1.1f);
		m_window.draw(m_menu);
		break;
	case Player::PLAYER_IN_GAME:		
		m_window.draw(m_levels[m_currentLevel]);
		for (Wave& wave : m_levels[m_currentLevel].getWaves())
		{
			wave.release(m_clock);
			m_window.draw(wave);
		}
	default:
		break;
	}
	m_window.display();
}

