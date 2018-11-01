#include "Game.h"


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
	m_levels[0].load("textures\\level_1.png", "levels\\level_1_track.png");
	
	/*std::vector<sf::Vector2f> trackLevel1_1920x1200
	{ sf::Vector2f(1920.0f, 688.0f),
	sf::Vector2f(1897.0f, 674.0f),
	sf::Vector2f(1745.0f, 627.0f),
	sf::Vector2f(1614.0f, 606.0f),
	sf::Vector2f(1492.0f, 599.0f),
	sf::Vector2f(1397.0f, 605.0f),
	sf::Vector2f(865.0f, 607.0f),
	sf::Vector2f(794.0f, 624.0f),
	sf::Vector2f(694.0f, 680.0f),
	sf::Vector2f(676.0f, 719.0f),
	sf::Vector2f(690.0f, 751.0f),
	sf::Vector2f(725.0f, 773.0f),
	sf::Vector2f(783.0f, 799.0f),
	sf::Vector2f(890.0f, 821.0f),
	sf::Vector2f(1028.0f, 828.0f),
	sf::Vector2f(1302.0f, 816.0f),
	sf::Vector2f(1395.0f, 816.0f),
	sf::Vector2f(1473.0f, 846.0f),
	sf::Vector2f(1513.0f, 887.0f),
	sf::Vector2f(1543.0f, 946.0f),
	sf::Vector2f(1553.0f, 999.0f),
	sf::Vector2f(1541.0f, 1035.0f),
	sf::Vector2f(1491.0f, 1083.0f),
	sf::Vector2f(1417.0f, 1106.0f),
	sf::Vector2f(1323.0f, 1110.0f),
	sf::Vector2f(958.0f, 1099.0f),
	sf::Vector2f(0.0f, 1014.0f) };
	m_levels[m_currentLevel].setTrack(trackLevel1_1920x1200);*/
	//_level
	//enemies
	Enemy en1(100, 5);
	Enemy en2(100, 3);
	m_enemies.push_back(en1);
	m_enemies.push_back(en2);
	m_enemies[0] = Enemy(420, 4);
	m_enemies[0].load("textures\\hotdog.png", sf::Vector2f(40, 40));//todo: return error if not
	m_enemies[1] = Enemy(420, 10);
	m_enemies[1].load("textures\\hotdog2.png", sf::Vector2f(40, 40));//todo: err
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
							/*for (Enemy& enemy : m_enemies)
							{							
								enemy.calculateTrack(m_levels[m_currentLevel].getTrack(), window.getSize(), m_levels[m_currentLevel].getSize());
								enemy.resetTimer();
							}*/
							//m_enemies[0].calculateTrack(m_levels[m_currentLevel].getTrack(), window.getSize(), m_levels[m_currentLevel].getSize());
							//m_enemies[0].resetTimer();
							m_enemies[1].setTrack(m_levels[m_currentLevel].getTrack());
							m_enemies[1].resetTimer();
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
		if (m_clock.getElapsedTime().asSeconds() > 1)
		{
			if (m_enemies[0].getActive() == false)
			{
				m_enemies[0].resetTimer();
				m_enemies[0].setActive(true);
			}				
			m_enemies[0].move();
			window.draw(m_enemies[0]);
		}
		if (m_clock.getElapsedTime().asSeconds() > 4)
		{
			if (m_enemies[1].getActive() == false)
			{
				m_enemies[1].resetTimer();
				m_enemies[1].setActive(true);
			}
			m_enemies[1].move();
			window.draw(m_enemies[1]);
		}
		break;
	default:
		break;
	}
	window.display();
}

